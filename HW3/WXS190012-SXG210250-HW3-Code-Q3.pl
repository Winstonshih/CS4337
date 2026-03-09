%Winston Shih (WXS190012)
%Satyam Garg (SXG210250)
%CS 4337.004 HW 3 Question 3
% Base case: empty list has 0 elements
elements([], 0).
% Case 1: Head is a list - recursively count its elements and add to tail count
elements([H|T], Count) :-
    is_list(H),
    elements(H, HCount),
    elements(T, TCount),
    Count is HCount + TCount.
% Case 2: Head is an atom/number - count it as 1 and add to tail count
elements([H|T], Count) :-
    \+ is_list(H),
    elements(T, TCount),
    Count is 1 + TCount.
