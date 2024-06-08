merge_sort([], []).
merge_sort([A], [A]).
merge_sort(List, Sorted) :-
    List = [_, _|_],
    split(List, L1, L2),
    merge_sort(L1, Sorted1),
    merge_sort(L2, Sorted2),
    merge(Sorted1, Sorted2, Sorted).

split([], [], []).
split([A], [A], []).
split([A, B|Rest], [A|Rest1], [B|Rest2]) :-
    split(Rest, Rest1, Rest2).

merge([], L, L).
merge(L, [], L) :- L \= [].
merge([A|RestA], [B|RestB], [A|Rest]) :-
    A =< B,
    merge(RestA, [B|RestB], Rest).
merge([A|RestA], [B|RestB], [B|Rest]) :-
    A > B,
    merge([A|RestA], RestB, Rest).