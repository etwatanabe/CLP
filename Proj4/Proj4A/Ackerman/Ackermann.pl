phi(M, N, 0, Result) :-
    Result is M + N.

phi(M, 0, 1, Result) :-
    Result is 0.

phi(M, 0, 2, Result) :-
    Result is 1.

phi(M, 0, P, Result) :-
    P > 0,
    Result is 1.

phi(M, N, P, Result) :-
    M > 0,
    N > 0,
    M1 is M - 1,
    N1 is N - 1,
    phi(M, N1, P, TempResult),
    phi(M1, TempResult, P, Result).

% (4,0) (3,7) (2,...)