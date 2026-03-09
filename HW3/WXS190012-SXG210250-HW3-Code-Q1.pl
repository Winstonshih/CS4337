%Winston Shih (WXS190012)
%Satyam Garg (SXG210250)
%CS 4337.004 HW 3 Question 1
% Checks if a number is prime by seeing if  it does not have a divisor starting with 2.
is_prime(N) :- 
    N > 1,
    \+ has_divisor(N, 2).
% Check if N has any divisor from D up to sqrt(N).
has_divisor(N, D) :-
    D * D =< N,
    N mod D =:= 0.
% Searches for a divisor of N up to square root of N.
has_divisor(N, D) :-
    D * D =< N, D1 is D + 1, has_divisor(N, D1).
% Check if a number is both prime and greater than 5
is_prime_gt5(N) :-
    N > 5, is_prime(N).
% Sum all numbers in a list that are prime and greater than 5
sum_prime_greater_than_5([], 0).
% Checks to see if H is a prime greater than 5.
sum_prime_greater_than_5([H|T], Sum) :-
    is_prime_gt5(H),
    sum_prime_greater_than_5(T, RestSum),
    Sum is H + RestSum.
%Checks to see if H is not a prime greater than 5.
sum_prime_greater_than_5([H|T], Sum) :-
    \+ is_prime_gt5(H),
    sum_prime_greater_than_5(T, Sum).