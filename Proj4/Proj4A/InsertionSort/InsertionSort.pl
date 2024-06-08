insertion_sort([], []).
insertion_sort([H|T], SortedList) :-
    insertion_sort(T, SortedT),
    insert(H, SortedT, SortedList).

% Insert an element into a sorted list.
insert(X, [], [X]).
insert(X, [H|T], [X,H|T]) :- X =< H.
insert(X, [H|T], [H|NT]) :- X > H, insert(X, T, NT).

% Test the insertion sort
test_insertion_sort :-
    insertion_sort([12, 11, 13, 5, 6], SortedList),
    write(SortedList), nl.
