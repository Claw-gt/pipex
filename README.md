## Introduction

Pipex is a project about pipe management. 

Its behaviour is explained with the following example:

| Execution | Equivalent outcome |
| :-------: | :----------------: |
|`./pipex infile "ls -l" "wc -l" outfile` | `<infile ls -l \| wc -l >outfile` |
