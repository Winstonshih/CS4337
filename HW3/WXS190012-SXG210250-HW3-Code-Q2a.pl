%Winston Shih (WXS190012)
%Satyam Garg (SXG210250)
%CS 4337.004 HW 3 Question 2 Bubble Sort
bubble_sort(List, SortedList) :-                  % Main bubble sort method.
    is_sorted(List),                              % Checks if List is already sorted.
    SortedList = List.                            % If List is sorted, then SortedList is set to List.
bubble_sort(List, SortedList) :-                  % Alternative bubble sort method (if List is not sorted).
    \+ is_sorted(List),                           % Verifies if List is not sorted.
    bubble_pass(List, TempList),                  % Performs a bubble sort through List with a TempList.
    bubble_sort(TempList, SortedList).            % Uses recursion calls to bubble sort List until fully sorted.
bubble_pass([], []).                              % Base case: The list is empty.
bubble_pass([X], [X]).                            % Base case: The list has one element
bubble_pass([X, Y | Rest], [Y, X | TempRest]) :-  % Case: List where first element is greater than second.
    X > Y,                                        % Checks if first element is greater than second.
    bubble_pass([Y | Rest], TempRest).            % Recursively bubble pass X with rest of list for comparison.
bubble_pass([X, Y | Rest], [X | TempRest]) :-     % Case: List where first element is smaller than second.
    X =< Y,                                       % Checks if first element is smaller than second.
    bubble_pass([Y | Rest], TempRest).            % Recursively bubble pass Y with rest of list for comparison.
is_sorted([]).                                    % Base case: Checks to see if empty list is sorted.
is_sorted([_]).                                   % Base case: Checks to see if one element list is sorted.
is_sorted([X, Y | Rest]) :-                       % Case: Check if 2 or more element list is sorted.
    X =< Y,                                       % Verify first element is less than or equal to second.
    is_sorted([Y | Rest]).                        % Recursively check if rest of 2 or more element list is sorted.