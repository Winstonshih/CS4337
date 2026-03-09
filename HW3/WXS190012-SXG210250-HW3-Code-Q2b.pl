%Winston Shih (WXS190012)
%Satyam Garg (SXG210250)
%CS 4337.004 HW 3 Question 2 Quick Sort
quicksort([], []).                   % Base case: Empty list is already sorted.
quicksort([X|Xs], Ys) :-             % Sort a list with X (first element) and Xs (remaining elements) into Ys.
    partition(Xs, X, Left, Right),   % Partition Xs into Left and Right subarrays with X as a pivot.
    quicksort(Left, Ls),             % Recursively sort the Left partition of Xs and store in Ls.
    quicksort(Right, Rs),            % Recursively sort the Right partition of Xs and store in Rs.
    append(Ls, [X|Rs], Ys).          % Combine: Combine Ls (left partition) and [X|Rs] (pivot and right partition).
                                     % Store combination into Ys.
partition([], _, [], []).            % Base case: Partition an empty list into two empty lists.
partition([X|Xs], Y, [X|Ls], Rs) :-  % Case: Partition a list when element X is less than pivot Y.
    X =< Y,                          % Check if X is less than or equal to pivot Y
    partition(Xs, Y, Ls, Rs).        % If true, then recursively partition Xs and X goes to left partition
partition([X|Xs], Y, Ls, [X|Rs]) :-  % Case: Partition a list when element X is greater than pivot Y.
    X > Y,                           % Check if element X is greater than pivot Y.
    partition(Xs, Y, Ls, Rs).        % If true, then recursively Xs and X goes to right partition
append([], Ys, Ys).                  % Base case: Appending empty list to Ys results in list of Ys.
append([X|Xs], Ys, [X|Zs]) :-        % Recursive case: Appending [X|Xs] to Ys results in list [X|Zs].
    append(Xs, Ys, Zs).              % Recursively append Xs and Ys to get Zs