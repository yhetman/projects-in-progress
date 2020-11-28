#!/bin/bash

from sklearn.metrics import roc_auc_score
from sklearn.tree import DecisionTreeClassifier, export_graphviz
import pandas as pd

RSEED = 1
df = pd.read_csv('students.csv')

y = df['is_enrolled']
x = df.drop(columns='is_enrolled')

print(df)
print(x)
print(y)

tree = DecisionTreeClassifier(max_depth=4)
tree.fit(x, y)

print('Model Accuracy : ' , tree.score(x,y))
print('Feature importance : ', tree.feature_importances_)
export_graphviz(tree,
        out_file = 'tree.dot',
        feature_names = ['math','physics','ukrainian','has_privilege'],
        class_names = ['0', '1'],
        rounded = True,
        proportion = False)

test = pd.read_csv('validation.csv')

tree_predictions = tree.predict(test)

tree_probabilities = tree.predict_proba(test)[:, 1]

print(tree_predictions)

print(tree_probabilities)

print(tree.decision_path(test))

labels = ['0','1','0','0','0','1','0','0','0','1','0']

roc_value = roc_auc_score(labels, tree_probabilities)

print('Model Accuracy : ' , tree.score(test, [int(i) for i in labels]))
