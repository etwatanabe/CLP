ls5x5(A11,A12,A13,A14,A15,
      A21,A22,A23,A24,A25,
      A31,A32,A33,A34,A35,
      A41,A42,A43,A44,A45,
      A51,A52,A53,A54,A55) :-
    perm5(A11,A12,A13,A14,A15),
    perm5(A21,A22,A23,A24,A25),
    perm5(A31,A32,A33,A34,A35),
    perm5(A41,A42,A43,A44,A45),
    perm5(A51,A52,A53,A54,A55),
    perm5(A11,A21,A31,A41,A51),
    perm5(A12,A22,A32,A42,A52),
    perm5(A13,A23,A33,A43,A53),
    perm5(A14,A24,A34,A44,A54),
    perm5(A15,A25,A35,A45,A55),
    prow5(A11,A12,A13,A14,A15),nl,
    prow5(A21,A22,A23,A24,A25),nl,
    prow5(A31,A32,A33,A34,A35),nl,
    prow5(A41,A42,A43,A44,A45),nl,
    prow5(A51,A52,A53,A54,A55),nl.

prow5(A, B, C, D, E) :-
    write(A), write(' '), write(B), write(' '), write(C), write(' '),
    write(D), write(' '), write(E).

perm5(A,B,C,D,E) :-
    neq5(A, B, C, D, E),
    num(A), num(B), num(C), num(D), num(E).

neq5(A,B,C,D,E) :- 
    neq(A,B), neq(A,C), neq(A,D), neq(A,E),
    neq(B,C), neq(B,D), neq(B,E),
    neq(C,D), neq(C,E),
    neq(D,E).

num(1). num(2). num(3). num(4). num(5).

neq(1,2). neq(1,3). neq(1,4). neq(1,5).
neq(2,1). neq(2,3). neq(2,4). neq(2,5).
neq(3,1). neq(3,2). neq(3,4). neq(3,5).
neq(4,1). neq(4,2). neq(4,3). neq(4,5).
neq(5,1). neq(5,2). neq(5,3). neq(5,4).