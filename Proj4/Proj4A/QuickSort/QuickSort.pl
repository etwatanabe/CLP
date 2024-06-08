% QuickSort in Prolog

% The entry point predicate
quicksort([], []).
quicksort([H|T], Sorted) :-
    partition(H, T, Left, Right),
    quicksort(Left, SortedLeft),
    quicksort(Right, SortedRight),
    append(SortedLeft, [H|SortedRight], Sorted).

% Partition the list into elements less than and greater than the pivot
partition(_, [], [], []).
partition(Pivot, [H|T], [H|Left], Right) :-
    H =< Pivot,
    partition(Pivot, T, Left, Right).
partition(Pivot, [H|T], Left, [H|Right]) :-
    H > Pivot,
    partition(Pivot, T, Left, Right).

% Append two lists
append([], L, L).
append([H|T], L, [H|R]) :-
    append(T, L, R).
