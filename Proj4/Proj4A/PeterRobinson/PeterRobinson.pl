A(0, N, Result) :-
    Result is N + 1.

A(M, 0, Result) :-
    M > 0,
    M1 is M - 1,
    A(M1, 1, Result).

A(M, N, Result) :-
    M > 0,
    N > 0,
    M1 is M - 1,
    N1 is N - 1,
    A(M, N1, TempResult),
    A(M1, TempResult, Result).

% (4,0) (3,7) (2,...)