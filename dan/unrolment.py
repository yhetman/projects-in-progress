#!/bin/bash

from sklearn.tree import DecisionTreeClassifier, export_graphviz
import pandas as pd

RSEED = 1
df = pd.read_csv('students.csv')

y = df['is_enrolled']
x = df.drop(columns='is_enrolled')

print(df)
print(x)
print(y)

tree = DecisionTreeClassifier(random_state=RSEED)
tree.fit(x, y)

print('Model Accuracy : ' , tree.score(x,y))

export_graphviz(tree,
        out_file = 'tree.dot',
        feature_names = ['math','physics','ukrainian','sum','has_privilege'],
        class_names = ['0', '1'],
        rounded = True,
        proportion = False)
