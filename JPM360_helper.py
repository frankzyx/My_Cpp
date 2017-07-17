import pandas as pd
pd.options.mode.chained_assignment = None

import numpy as np
from scipy import stats

import seaborn as sns
sns.set(font_scale = 1.2)

from statsmodels.formula.api import ols
import re
from sklearn.metrics import roc_curve, auc

######################################################################################
def addImportantColumns(df):
    # extract the year of default
    df['default_year'] = df['eom_default_date'].apply(lambda x: int(x[:4]))

    # define observed LGD = "LGD_DISC_unresAdj_WC_rolled_CAP"
    df['observed_lgd'] = df['LGD_DISC_unresAdj_WC_rollup_CAP']

    # define assigned LGD = "facility_lgd" rescaled as percentage
    df['assigned_lgd'] = df['facility_lgd'].apply(lambda x: x / 100)

    # define the error in LGD prediction
    df['error_lgd'] = df['assigned_lgd'] - df['observed_lgd']

    # conservative prediction
    df['is_conservative'] = (df['assigned_lgd'] >= df['observed_lgd'])



def regressionPlot(data):
    g = sns.JointGrid(x="assigned_lgd", y="observed_lgd", data=data, size=10)  # JointGrid
    g = g.plot_joint(sns.regplot, line_kws={'color':'g'})    # joint plot for x and y
    g = g.plot_marginals(sns.distplot, kde=False, color='0.5')
    # rsquare = lambda a, b: stats.pearsonr(a, b)[0] ** 2    # r-squared = correlation ^ 2
    # g = g.annotate(rsquare, template="{stat}: {val:.2f}", stat="$R^2$", loc="upper left", fontsize=18)
    # g = g.annotate(stats.spearmanr)


    
def countElements(lst):
    d = dict()
    for element in lst:
        if element is not None:
            if element not in d:
                d[element] = 0
            d[element] += 1
    return d



def getTreeBranchName(s):
    ''' Parse the string s to extract tree names.
        Input: string s.
        Output: (treeName, branchName) - strings.
    '''
    tree = re.split(':', s, maxsplit=1)
    if 'Muni' in tree[0]:
        tree[0] = 'Muni'
    elif 'Asset' in tree[0]:
        tree[0] = 'Asset Rcvy Liq'
    branch = re.split('/', tree[1], maxsplit=1)
    return [tree[0].strip(), branch[1].strip()]



def basicStatisticalAnalysis(df):
    # X = df.assigned_lgd
    # X = sm.add_constant(X)
    # y = df.observed_lgd
    result = ols("observed_lgd ~ assigned_lgd", df).fit()
    print(result.summary())


    
def label_predictions(df, model, threshold):
    columnName = 'roc_label_' + model
    df[columnName] = df[model].apply(lambda x: 1 if x >= threshold else 0)



def is_sorted(lst):
    if len(lst) <= 1:
        return True
    return all(lst[i] <= lst[i+1] for i in range(len(lst)-1)) |\
           all(lst[i] >= lst[i+1] for i in range(len(lst)-1))



def computeCorrelation(df, a, b='observed_lgd'):
    pearson, _ = stats.pearsonr(df[a], df[b])
    spearman, _ = stats.spearmanr(df[a], df[b])
    kendall, _ = stats.kendalltau(df[a], df[b])
    return [pearson, spearman, kendall]

    
def addErrorColumns(df, modelNames):
    for model in modelNames:
        df[model + '_error'] = df[model] - df['observed_lgd']



def generate_roc_curve(df, model, actual_threshold, thresholds):
    ''' Generate the receiver operating characteristic curve.
        Input: 
            df: data frame
            model: model name
            actual_threshold: the threshold for actual labeling
            thresholds: a list of threshold values for the model
        Output:
            fpr: false positive rate = sensitivity
            tpr: true positive rate = 1 - specificity
        Can be used in cross-validation as well.
    '''
    n = len(thresholds)
    columnName = 'roc_label_' + model
    fpr = np.zeros(n)
    tpr = np.zeros(n)

    # first label the observed_lgd as High or Low
    df['roc_observed'] = df['observed_lgd'].apply(lambda x: 1 if x >= actual_threshold else 0)
    P = df['roc_observed'].sum()
    N = df.shape[0] - P

    for i in range(n):
        # then label the model predicted lgd as High or Low
        columnName = 'roc_label_' + model
        df[columnName] = df[model].apply(lambda x: 1 if x >= thresholds[i] else 0)
        
        # calculate the FPR and TPR
        fp_count = ((df.roc_observed == 0) & (df[columnName] == 1)).sum()
        tp_count = ((df.roc_observed == 1) & (df[columnName] == 1)).sum()
        fpr[i] = fp_count / N
        tpr[i] = tp_count / P

    return [fpr, tpr]



######################################################################################
def validation_switch(X_train, X_test, t_list, mse, mae, mse_sd, mae_sd, areaUnderCurve, model):
    '''Given train and test split, compute the summary statistics of each method.
    '''
    rescale = np.sqrt(X_test.shape[0])
    hist_avg = X_train['observed_lgd'].mean()
    
    # 1. ROC curve: Must do it first, because the error term will modify the dataframe
    fpr, tpr = generate_roc_curve(X_test, model, X_train['observed_lgd'].mean(), t_list)
#     plt.plot(fpr, tpr, '--')
    areaUnderCurve.append(auc(fpr, tpr))

    # 2. switch among models for the MSE and MAE
    if model == 'hist_avg': 
        error = hist_avg
    elif model == 'treewise_avg':
        # create the "tree : mean-value" dictionary for look-up
        tree_dict = dict(X_train.groupby('tree_name').mean()['observed_lgd'])
        # predict on the test set: add a column
        X_test['predicted_lgd'] = X_test['tree_name'].apply(lambda name: \
                                    tree_dict[name] if name in tree_dict else hist_avg)
        error = X_test['predicted_lgd']
    elif model == 'branchwise_avg':
        # create the "tree : mean-value" dictionary for look-up
        branch_dict = dict(X_train.groupby('branch_name').mean()['observed_lgd'])
        # predict on the test set: add a column
        X_test['predicted_lgd'] = X_test['branch_name'].apply(lambda name: \
                                    branch_dict[name] if name in branch_dict else hist_avg)
        error = X_test['predicted_lgd']
    elif model == 'assigned_lgd':
        error = X_test['assigned_lgd']
    
    # make sure to subtract the observed_lgd from original error term
    error -= X_test['observed_lgd']

    # append the statistics to the list
    mse.append((error**2).mean())
    mae.append(abs(error).mean())
    mse_sd.append((error**2).std() / rescale)
    mae_sd.append(abs(error).std() / rescale)

def cross_validation_benchmarks(df, model, CV, t_list, isTraining=False):
    mse, mse_sd, mae, mae_sd, areaUnderCurve = [], [], [], [], []
    for train_idx, test_idx in CV:
        # split into train and test sets
        X_train, X_test = df.iloc[train_idx], df.iloc[test_idx]
        if not isTraining:
            validation_switch(X_train, X_test, t_list, mse, mae, mse_sd, mae_sd, areaUnderCurve, model)
        else:
            validation_switch(X_train, X_train, t_list, mse, mae, mse_sd, mae_sd, areaUnderCurve, model)
    return np.c_[mse, mse_sd, mae, mae_sd, areaUnderCurve]

def walk_forwark_validation(df, model, t_list, isTraining=False):
    mse, mse_sd, mae, mae_sd, areaUnderCurve = [], [], [], [], []
    for currYear in range(2009, 2014):
        X_train, X_test = df[df.default_year <= currYear], df[df.default_year == currYear]  
        if not isTraining:
            validation_switch(X_train, X_test, t_list, mse, mae, mse_sd, mae_sd, areaUnderCurve, model)
        else:
            validation_switch(X_train, X_train, t_list, mse, mae, mse_sd, mae_sd, areaUnderCurve, model)
    return np.c_[mse, mse_sd, mae, mae_sd, areaUnderCurve]