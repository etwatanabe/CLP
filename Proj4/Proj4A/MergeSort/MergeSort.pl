merge_sort([], []).
merge_sort([A], [A]).
merge_sort(List, Sorted) :-
    List = [_, _|_],
    divide(List, L1, L2),
    merge_sort(L1, Sorted1),
    merge_sort(L2, Sorted2),
    merge(Sorted1, Sorted2, Sorted).

divide([], [], []).
divide([A], [A], []).
divide([A, B | Rest], [A | Rest1], [B | Rest2]) :-
    divide(Rest, Rest1, Rest2).

merge([], L, L).
merge(L, [], L).
merge([A | L1], [B | L2], [A | L3]) :-
    A =< B,
    merge(L1, [B | L2], L3).
merge([A | L1], [B | L2], [B | L3]) :-
    A > B,
    merge([A | L1], L2, L3).
