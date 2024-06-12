bubble_sort(List, Sorted) :-
    swap(List, List1), !,
    bubble_sort(List1, Sorted).
bubble_sort(Sorted, Sorted).

swap([X, Y | Rest], [Y, X | Rest]) :-
    X > Y.
swap([Z | Rest], [Z | Rest1]) :-
    swap(Rest, Rest1).
