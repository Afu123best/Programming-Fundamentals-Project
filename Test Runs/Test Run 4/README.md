Test Run 4 (Just going to continue from Test Run 3):
fixed bug from test run 3. so just needed to add these two lines since \n was causing a few problems in the input stream buffer. cin.ignore() and cin.ignore(10000,'\n') 
Ongoing
1.
Test Case 1 = Passed
Test Case 2 = Passed
Test Case 3 = Passed
2.
Test Case 4 = Passed
Test Case 5 = Passed
Test Case 6 = Passed (but bugged the input console a bit. It basically removes the 50th character which is '\n')

3.
Test Case 7 = Passed
Test Case 8 = Passed
Test Case 9 = Passed
Test Case 10 = Passed
Test Case 11 = Passed
Test Case 12 = Passed

4.
Test Case 13 = Passed
Test Case 14 = Weird
