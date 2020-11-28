#!/bin/bash

from sklearn.metrics import roc_auc_score
from sklearn.tree import DecisionTreeClassifier, export_graphviz
import pandas as pd
import os

RSEED = 1

df = pd.read_csv('students.csv')
y = df['is_enrolled']
x = df.drop(columns='is_enrolled')

Dtree = DecisionTreeClassifier(random_state=RSEED)
Dtree = Dtree.fit(x, y)

print('Model Accuracy : ' , Dtree.score(x,y))
print('Feature importance : ', Dtree.feature_importances_)

os.system('dot -Tpng tree.dot -o tree.png -Gdpi=60')
print('Now you can check the image of tree')

export_graphviz(Dtree,
        out_file = 'tree.dot',
        feature_names = ['math','physics','ukrainian','has_privilege'],
        class_names = ['0', '1'],
        rounded = True,
        proportion = False)

test_x = pd.read_csv('validation.csv')
test_y = ['0','1','0','0','0','1','0','0','0','1','0']

tree_predictions = Dtree.predict(test_x)

tree_probabilities = Dtree.predict_proba(test_x)[:, 1]

roc_value = roc_auc_score(test_y, tree_probabilities)

print('Model results: ' , Dtree.score(test_x, [int(i) for i in test_y]))

