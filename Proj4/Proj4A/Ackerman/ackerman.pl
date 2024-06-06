ackermann(0, N, Result) :-
    Result is N + 1.

ackermann(M, 0, Result) :-
    M > 0,
    M1 is M - 1,
    ackermann(M1, 1, Result).

ackermann(M, N, Result) :-
    M > 0,
    N > 0,
    M1 is M - 1,
    N1 is N - 1,
    ackermann(M, N1, TempResult),
    ackermann(M1, TempResult, Result).

% (4,0) (3,7) (2,...)