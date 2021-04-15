# Introduction
* While designing a circuit, depending on our requirement, certain times odd values of resistance are required in the circuit, values which are not directly available as standard valued resistors. So this utility aims to provide best combinations of standard resistors which can be used.

# Cost and Features
* Will provide series as well as parallel combination of resistors suitable for the required odd value.
# SWOT Analysis
![SWOT analysis](https://github.com/261833/Prachiproject/blob/main/1_Requirements/SWOT%20analysis.png)
# 4W's and 1'H
## Who:
* Circuit designers

## What:
* The task of searching for standard value resistors to combine and yield your required value of resistance becomes complicated and hence it can turn out to be helpful

## When:
* On encountering a odd value resistor requirement while designing circuit

## Where:
* Industries designing circuits, in labs 

## How
* User can just choose the tolerance value required, and enter the required resistance value and the possible combinations would be displayed

# Detail requirements
## High Level Requirements
ID	| Description	| Category	| Status|
----| ------------|-----------|-------|
HR01	|User shall be able to select tolerance value|	Techincal	|IMPLEMENTED
HR02	|User can enter the required resistance value|	Techincal|	IMPLEMENTED
HR03	|User can get the possible combinations|	Techincal|	IMPLEMENTED
## Low Level Requirements
ID	| Description	| HLR ID	| Status|
----| ------------|-----------|-------|
LR01	|An array of values specific to the required tolerance shall be created|	HR01	|IMPLEMENTED
LR02a	|Finding the index of value nearest to the entered value|	HR02|	IMPLEMENTED
LR02b	|Finding the index of second resistor in combination for series output|	HR02|	IMPLEMENTED
LR02c	|Finding the index of second resistor in combination for parallel output|	HR02|	IMPLEMENTED
LR02d	|Calculating tolerance values of respective combinations|	HR02|	IMPLEMENTED
LR03a	|Sorting the results in ascending order of tolerance|	HR03|	IMPLEMENTED
LR03b	|Printing the combinations|	HR03|	IMPLEMENTED

