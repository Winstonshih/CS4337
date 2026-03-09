%Winston Shih (WXS190012)
%Satyam Garg (SXG210250)
%CS 4337.004 HW 3 Question 4
% Genders of family members
male(winston).
male(billy).
male(jack).
male(tom).
male(leo).
male(alex).
male(mike).
male(george).
male(harry).
male(peter).
male(connor).       
female(fiona).
female(audrey).
female(ella).
female(nancy).
female(lisa).
female(sarah).
female(mary).
female(julia).     
female(susan).       
% Parental relationships.
parent(billy, winston).
parent(fiona, winston).
parent(billy, audrey).
parent(fiona, audrey).
parent(jack, fiona).
parent(ella, fiona).
parent(tom, billy).
parent(lisa, billy).
parent(jack, leo).
parent(ella, leo).
parent(alex, nancy).
parent(audrey, nancy).
parent(billy, sarah).
parent(fiona, sarah).
parent(billy, mike).
parent(fiona, mike).
parent(george, jack).
parent(harry, george).
parent(tom, mary).
parent(audrey, julia).
parent(alex, julia).
parent(audrey, peter).
parent(jack, susan).    
parent(ella, susan).
parent(susan, connor). 
% Parent rules
mother(X, Y) :- parent(X, Y), female(X).
father(X, Y) :- parent(X, Y), male(X).
% Sibling rules.
sibling(X, Y) :-
    father(F, X), father(F, Y),
    mother(M, X), mother(M, Y),
    X \== Y.
%Sister and brother rules.
sister(X, Y) :- sibling(X, Y), female(X).
brother(X, Y) :- sibling(X, Y), male(X).
% Grandparents and great grandparents rules
grandparent(X, Y) :- parent(X, Z), parent(Z, Y).
grandfather(X, Y) :- grandparent(X, Y), male(X).
grandmother(X, Y) :- grandparent(X, Y), female(X).
great_grandparent(X, Y) :- parent(X, Z), grandparent(Z, Y).
great_grandfather(X, Y) :- great_grandparent(X, Y), male(X).
great_grandmother(X, Y) :- great_grandparent(X, Y), female(X).
great_great_grandparent(X, Y) :- parent(X, Z), great_grandparent(Z, Y).
great_great_grandfather(X, Y) :- great_great_grandparent(X, Y), male(X).
% Uncle and aunt rules.
uncle(X, Y) :- brother(X, Z), parent(Z, Y).
aunt(X, Y) :- sister(X, Z), parent(Z, Y).
% Cousin rule.
cousin(X, Y) :- parent(Z, X), parent(W, Y), sibling(Z, W).
% Niece and nephew rules.
niece(X, Y) :- parent(Z, X), sibling(Z, Y), female(X).
nephew(X, Y) :- parent(Z, X), sibling(Z, Y), male(X).
% Count brothers algorithm.
count_brothers(Person, Count) :-
    findall(B, brother(B, Person), Brothers),
    length(Brothers, Count).