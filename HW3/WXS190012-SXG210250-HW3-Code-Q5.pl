% Winston Shih (WXS190012)
% Satyam Garg (SXG210250)
% CS 4337.004
% CS 4337 HW 3 Question 5
% Define available colors for Europe map
color(red).
color(green).
color(blue).
color(yellow).
% Define all countries in Europe
country(albania).
country(andorra).
country(austria).
country(belarus).
country(belgium).
country(bosnia_herzegovina).
country(bulgaria).
country(croatia).
country(cyprus).
country(czech_republic).
country(denmark).
country(estonia).
country(finland).
country(france).
country(germany).
country(greece).
country(hungary).
country(iceland).
country(ireland).
country(italy).
country(kosovo).
country(latvia).
country(liechtenstein).
country(lithuania).
country(luxembourg).
country(malta).
country(moldova).
country(monaco).
country(montenegro).
country(netherlands).
country(north_macedonia).
country(norway).
country(poland).
country(portugal).
country(romania).
country(russia).
country(san_marino).
country(serbia).
country(slovakia).
country(slovenia).
country(spain).
country(sweden).
country(switzerland).
country(turkey).
country(ukraine).
country(united_kingdom).
country(vatican_city).
% Countries adjacent to Albania.
adjacent(albania, montenegro).
adjacent(albania, kosovo).
adjacent(albania, north_macedonia).
adjacent(albania, greece).
% Countries adjacent to Andorra.
adjacent(andorra, france).
adjacent(andorra, spain).
% Countries adjacent to Austria.
adjacent(austria, germany).
adjacent(austria, czech_republic).
adjacent(austria, slovakia).
adjacent(austria, hungary).
adjacent(austria, slovenia).
adjacent(austria, italy).
adjacent(austria, switzerland).
adjacent(austria, liechtenstein).
% Countries adjacent to Belarus.
adjacent(belarus, latvia).
adjacent(belarus, lithuania).
adjacent(belarus, poland).
adjacent(belarus, ukraine).
adjacent(belarus, russia).
% Countries adjacent to Belgium.
adjacent(belgium, france).
adjacent(belgium, luxembourg).
adjacent(belgium, germany).
adjacent(belgium, netherlands).
% Countries to Bosnia and Herzegovina
adjacent(bosnia_herzegovina, croatia).
adjacent(bosnia_herzegovina, serbia).
adjacent(bosnia_herzegovina, montenegro).
% Countries to Bulgaria.
adjacent(bulgaria, romania).
adjacent(bulgaria, serbia).
adjacent(bulgaria, north_macedonia).
adjacent(bulgaria, greece).
adjacent(bulgaria, turkey).
% Countries to Croatia.
adjacent(croatia, slovenia).
adjacent(croatia, hungary).
adjacent(croatia, serbia).
adjacent(croatia, bosnia_herzegovina).
adjacent(croatia, montenegro).
% Countries to Czech Republic.
adjacent(czech_republic, germany).
adjacent(czech_republic, poland).
adjacent(czech_republic, slovakia).
adjacent(czech_republic, austria).
% Countries adjacent to Denmark.
adjacent(denmark, germany).
% Countries adjacent to Estonia.
adjacent(estonia, russia).
adjacent(estonia, latvia).
% Countries adjacent to Finland.
adjacent(finland, sweden).
adjacent(finland, norway).
adjacent(finland, russia).
% Countries adjacent to France.
adjacent(france, spain).
adjacent(france, andorra).
adjacent(france, monaco).
adjacent(france, italy).
adjacent(france, switzerland).
adjacent(france, germany).
adjacent(france, luxembourg).
adjacent(france, belgium).
% Countries adjacent to Germany
adjacent(germany, denmark).
adjacent(germany, netherlands).
adjacent(germany, belgium).
adjacent(germany, luxembourg).
adjacent(germany, france).
adjacent(germany, switzerland).
adjacent(germany, austria).
adjacent(germany, czech_republic).
adjacent(germany, poland).
% Countries adjacent to Greece.
adjacent(greece, albania).
adjacent(greece, north_macedonia).
adjacent(greece, bulgaria).
adjacent(greece, turkey).
% Countries adjacent to Hungary.
adjacent(hungary, austria).
adjacent(hungary, slovakia).
adjacent(hungary, ukraine).
adjacent(hungary, romania).
adjacent(hungary, serbia).
adjacent(hungary, croatia).
adjacent(hungary, slovenia).
% Countries adjacent to Italy.
adjacent(italy, france).
adjacent(italy, switzerland).
adjacent(italy, austria).
adjacent(italy, slovenia).
adjacent(italy, san_marino).
adjacent(italy, vatican_city).
% Countries adjacent to Kosovo.
adjacent(kosovo, serbia).
adjacent(kosovo, north_macedonia).
adjacent(kosovo, albania).
adjacent(kosovo, montenegro).
% Countries adjacent to Latvia.
adjacent(latvia, estonia).
adjacent(latvia, russia).
adjacent(latvia, belarus).
adjacent(latvia, lithuania).
% Countries adjacent to Liechtenstein.
adjacent(liechtenstein, switzerland).
adjacent(liechtenstein, austria).
% Countries adjacent to Lithuania.
adjacent(lithuania, latvia).
adjacent(lithuania, belarus).
adjacent(lithuania, poland).
adjacent(lithuania, russia).
% Countries adjacent to Luxembourg.
adjacent(luxembourg, belgium).
adjacent(luxembourg, germany).
adjacent(luxembourg, france).
% Countries adjacent to Moldova.
adjacent(moldova, romania).
adjacent(moldova, ukraine).
% Countries adjacent to Monaco.
adjacent(monaco, france).
% Countries adjacent to Montenegro.
adjacent(montenegro, croatia).
adjacent(montenegro, bosnia_herzegovina).
adjacent(montenegro, serbia).
adjacent(montenegro, kosovo).
adjacent(montenegro, albania).
% Countries adjacent to Netherlands.
adjacent(netherlands, germany).
adjacent(netherlands, belgium).
% Countries adjacent to North Macedonia.
adjacent(north_macedonia, kosovo).
adjacent(north_macedonia, serbia).
adjacent(north_macedonia, bulgaria).
adjacent(north_macedonia, greece).
adjacent(north_macedonia, albania).
% Countries adjacent to Norway.
adjacent(norway, sweden).
adjacent(norway, finland).
adjacent(norway, russia).
% Countries adjacent to Poland.
adjacent(poland, germany).
adjacent(poland, czech_republic).
adjacent(poland, slovakia).
adjacent(poland, ukraine).
adjacent(poland, belarus).
adjacent(poland, lithuania).
adjacent(poland, russia).
% Countries adjacent to Portugal.
adjacent(portugal, spain).
% Romania
adjacent(romania, ukraine).
adjacent(romania, moldova).
adjacent(romania, bulgaria).
adjacent(romania, serbia).
adjacent(romania, hungary).
% European countries adjacent to Russia. 
adjacent(russia, norway).
adjacent(russia, finland).
adjacent(russia, estonia).
adjacent(russia, latvia).
adjacent(russia, lithuania).
adjacent(russia, poland).
adjacent(russia, belarus).
adjacent(russia, ukraine).
% Countries adjacent to San Marino.
adjacent(san_marino, italy).
% Countries adjacent to Serbia.
adjacent(serbia, hungary).
adjacent(serbia, romania).
adjacent(serbia, bulgaria).
adjacent(serbia, north_macedonia).
adjacent(serbia, kosovo).
adjacent(serbia, montenegro).
adjacent(serbia, bosnia_herzegovina).
adjacent(serbia, croatia).
% Countries adjacent to Slovakia.
adjacent(slovakia, czech_republic).
adjacent(slovakia, poland).
adjacent(slovakia, ukraine).
adjacent(slovakia, hungary).
adjacent(slovakia, austria).
% Countries adjacent to Slovenia.
adjacent(slovenia, austria).
adjacent(slovenia, italy).
adjacent(slovenia, croatia).
adjacent(slovenia, hungary).
% Countries adjacent to Spain.
adjacent(spain, portugal).
adjacent(spain, france).
adjacent(spain, andorra).
% Countries adjacent to Sweden.
adjacent(sweden, norway).
adjacent(sweden, finland).
% Countries adjacent to Switzerland.
adjacent(switzerland, germany).
adjacent(switzerland, austria).
adjacent(switzerland, liechtenstein).
adjacent(switzerland, italy).
adjacent(switzerland, france).
% European countries adjacent to Turkey.
adjacent(turkey, greece).
adjacent(turkey, bulgaria).
% Countries adjacent to Ukraine.
adjacent(ukraine, poland).
adjacent(ukraine, slovakia).
adjacent(ukraine, hungary).
adjacent(ukraine, romania).
adjacent(ukraine, moldova).
adjacent(ukraine, russia).
adjacent(ukraine, belarus).
% Countries adjacent to United Kingdom.
adjacent(united_kingdom, ireland).
% Countries adjacent to Vatican City.
adjacent(vatican_city, italy).
% Optimized predicate to find a coloring using constraint checking during assignment
find_coloring(Colors) :-
    setof(Country, country(Country), Countries),
    sort_by_neighbors(Countries, SortedCountries),
    assign_colors(SortedCountries, [], Colors).
% Sort countries by number of neighbors (most constrained first)
sort_by_neighbors(Countries, Sorted) :-
    findall(Count-Country, (
        member(Country, Countries),
        count_neighbors(Country, Count)
    ), Pairs),
    sort(0, @>=, Pairs, SortedPairs),
    findall(C, member(_-C, SortedPairs), Sorted).
% Count neighbors for a country
count_neighbors(Country, Count) :-
    findall(N, (adjacent(Country, N); adjacent(N, Country)), Neighbors),
    length(Neighbors, Count).
% Assign colors with early constraint checking
assign_colors([], Acc, Acc).
assign_colors([Country|Rest], Acc, Result) :-
    color(Color),
    \+ conflicts_with_assigned(Country, Color, Acc),
    assign_colors(Rest, [Country-Color|Acc], Result).
% Check if assigning Color to Country conflicts with already assigned countries
conflicts_with_assigned(Country, Color, Assigned) :-
    member(OtherCountry-Color, Assigned),
    (adjacent(Country, OtherCountry) ; adjacent(OtherCountry, Country)).
% Helper to find and display a coloring
solve_and_display :-
    find_coloring(Colors),
    write('Valid coloring found:'), nl,
    print_colors(Colors).
% Print the coloring
print_colors([]).
print_colors([Country-Color|Rest]) :-
    write(Country), write(' -> '), write(Color), nl,
    print_colors(Rest).
% Count how many countries use each color
count_color_usage(Colors) :-
    findall(C, member(_-C, Colors), AllColors),
    count_occurrences(AllColors, red, RedCount),
    count_occurrences(AllColors, green, GreenCount),
    count_occurrences(AllColors, blue, BlueCount),
    count_occurrences(AllColors, yellow, YellowCount),
    write('Color usage:'), nl,
    write('Red: '), write(RedCount), nl,
    write('Green: '), write(GreenCount), nl,
    write('Blue: '), write(BlueCount), nl,
    write('Yellow: '), write(YellowCount), nl.
count_occurrences([], _, 0).
count_occurrences([H|T], H, N) :-
    count_occurrences(T, H, N1),
    N is N1 + 1.
count_occurrences([H|T], X, N) :-
    H \= X,
    count_occurrences(T, X, N).