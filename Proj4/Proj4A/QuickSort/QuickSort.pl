quick_sort([], []).
quick_sort([H|T], Sorted) :-
    partition(H, T, L, G),
    quick_sort(L, SortedL),
    quick_sort(G, SortedG),
    append(SortedL, [H|SortedG], Sorted).

partition(_, [], [], []).
partition(H, [X|T], [X|L], G) :-
    X =< H,
    partition(H, T, L, G).
partition(H, [X|T], L, [X|G]) :-
    X > H,
    partition(H, T, L, G).
