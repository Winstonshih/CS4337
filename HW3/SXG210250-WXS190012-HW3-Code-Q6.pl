%Satyam Garg(SXG210250)
%Winston Shih(WXS190012)
%CS 4337.004 HW 3 Question 6
% --- Section 1: Facts ---
country_data('Asia', 559056, 19624, 295674, 243758, 5363).
  country_data('Turkey', 126045, 3397, 63151, 59497, 1424).
country_data('Iran', 97424, 6203, 78422, 12799, 2690).
    country_data('China', 82880, 4633, 77766, 481, 33).
country_data('India', 42533, 1391, 11775, 29367, 0).
 country_data('Saudi Arabia', 27011, 184, 4134, 22693, 139).
country_data('Pakistan', 20186, 462, 5590, 14134, 111).
  country_data('Singapore', 18205, 18, 1408, 16779, 22).
 country_data('Israel', 16208, 232, 9749, 6227, 103).

% --- Section 2: Helper Rules ---

sum_list([],0).
sum_list([H|T], Total) :-
    sum_list(T, Rest),
    Total is H + Rest.

% A much clunkier way to find the max value in a list
max_list([H], H).
max_list([H|T], H) :- max_list(T, T_Max), H >= T_Max, !.
max_list([_|T], T_Max) :- max_list(T, T_Max).

% Same clunky logic for the min value
min_list([H], H).
min_list([H|T], H) :- min_list(T, T_Min), H =< T_Min, !.
min_list([_|T], T_Min) :- min_list(T, T_Min).

% A hand-made length function instead of the built-in one
my_length([],0).
my_length([_|T], Len) :-
    my_length(T, LenOfTail),
    Len is LenOfTail + 1.

% --- Section 3: Rules for Answering Corrected Questions ---

% A. Which country has the smallest number of Total cases?
question_a(TheCountry) :-
    findall(Cases, (country_data(C, Cases, _, _, _, _), C \= 'Asia'), AllTheCases),
    min_list(AllTheCases, MinC),
    country_data(TheCountry, MinC, _, _, _, _).

% B. Which country has the largest number of total deaths?
question_b(DaCountry) :-
    findall(D, country_data(_, _, D, _, _, _), DeathList),
    max_list(DeathList, MaxD),
    country_data(DaCountry, _, MaxD, _, _, _).

% C. Which country/countries has/have the largest case number or the smallest number of total deaths?
question_c(Result) :- % part 1
    findall(C, country_data(_,C,_,_,_,_), AllCases),
    max_list(AllCases, MaxVal),
    country_data(Result, MaxVal, _, _, _, _).
question_c(Result) :- % part 2
    findall(D, country_data(_,_,D,_,_,_), AllDeaths),
    min_list(AllDeaths, MinVal),
    country_data(Result, _, MinVal, _, _, _).

% D. How many active cases are reported in total for Asia, Turkey, and Iran?
question_d(Total) :-
    country_data('Asia', _, _, _, Active1, _),
    country_data('Turkey', _, _, _, Active2, _),
    country_data('Iran', _, _, _, Active3, _),
    Total is Active1 + Active2+Active3.

% E. Which country/countries has/have more than 1000 serious cases?
question_e(C) :-
    country_data(C, _, _, _, _, Srs),
    Srs > 1000.

% F. Which country has/have more than number of deaths in India?
question_f(CountryName) :-
    country_data('India', _, DeathsInIndia, _, _, _),
    country_data(CountryName, _, OtherDeaths, _, _, _),
    CountryName \= 'India',
    OtherDeaths > DeathsInIndia.

% G. Which country has/have less than number of deaths in India?
question_g(SomeCountry) :-
    country_data('India', _, IndDeaths, _, _, _),
    country_data(SomeCountry, _, CtryDeaths, _, _, _),
    SomeCountry \= 'India',
    CtryDeaths < IndDeaths.

% H. What is sum of the serious cases in this report?
question_h(SumValue) :-
    findall(S, country_data(_,_,_,_,_,S), ListOfSerious),
    sum_list(ListOfSerious, SumValue).

% I. What is the average of death in this report?
question_i(Avg) :-
    findall(Deaths, country_data(_, _, Deaths, _, _, _), AllDeaths),
    sum_list(AllDeaths, Sum),
    my_length(AllDeaths, Count),
    Avg is Sum / Count.

% J. Which country/countries has/have done less than 100k total cases?
question_j(C) :-
    country_data(C, TC, _, _, _, _),
    C \= 'Asia',
    TC < 100000.

% K. Which country/countries has/have done less than 100k and grater than 50 total cases?
question_k(Country) :-
    country_data(Country, Cases, _, _, _, _),
    Country \= 'Asia',
    Cases < 100000,
    Cases > 50.

% L. Which country/countries has/have reported no deaths?
question_l(Country) :-
    country_data(Country, _, 0, _, _, _).

% M. Sort the counties based on the number of serious cases in ascending order.
question_m(Sorted) :-
    findall(Num-C, country_data(C,_,_,_,_,Num), PairList),
    keysort(PairList, Sorted).


% --- Section 4: Main Rule to Show All Answers ---

show_all_answers :-
    writeln('Q A: Which country has the smallest number of Total cases?'),
    question_a(AnsA), write('A A: '), writeln(AnsA),
    writeln('Q B: Which country has the largest number of total deaths?'),
    question_b(AnsB), write('A B: '), writeln(AnsB),
    writeln('Q C: Which country/countries has/have the largest case number or the smallest number of total deaths?'),
    findall(Res, question_c(Res), ListC), write('A C: '), writeln(ListC),
    writeln('Q D: How many active cases are reported in total for Asia, Turkey, and Iran?'),
    question_d(AnsD), write('A D: '), writeln(AnsD),
    writeln('Q E: Which country/countries has/have more than 1000 serious cases?'),
    findall(Res, question_e(Res), ListE), write('A E: '), writeln(ListE),
    writeln('Q F: Which country has/have more than number of deaths in India?'),
    findall(Res, question_f(Res), ListF), write('A F: '), writeln(ListF),
    writeln('Q G: Which country has/have less than number of deaths in India?'),
    findall(Res, question_g(Res), ListG), write('A G: '), writeln(ListG),
    writeln('Q H: What is sum of the serious cases in this report?'),
    question_h(AnsH), write('A H: '), writeln(AnsH),
    writeln('Q I: What is the average of death in this report?'),
    question_i(AnsI), write('A I: '), writeln(AnsI),
    writeln('Q J: Which country/countries has/have done less than 100k total cases?'),
    findall(Res, question_j(Res), ListJ), write('A J: '), writeln(ListJ),
    writeln('Q K: Which country/countries has/have done less than 100k and grater than 50 total cases?'),
    findall(Res, question_k(Res), ListK), write('A K: '), writeln(ListK),
    writeln('Q L: Which country/countries has/have reported no deaths?'),
    ( findall(C, question_l(C), L), L \= [] ->
        write('A L: '), writeln(L)
    ;
        writeln('A L: No country in the report has zero deaths.')
    ),
    writeln('Q M: Sort the counties based on the number of serious cases in ascending order.'),
    question_m(AnsM), write('A M: '), writeln(AnsM).