ls4x4(A11, A12, A13, A14,
      A21, A22, A23, A24,
      A31, A32, A33, A34,
      A41, A42, A43, A44) :-
    perm4(A11, A12, A13, A14),
    perm4(A21, A22, A23, A24),
    perm4(A31, A32, A33, A34),
    perm4(A41, A42, A43, A44),
    perm4(A11, A21, A31, A41),
    perm4(A12, A22, A32, A42),
    perm4(A13, A23, A33, A43),
    perm4(A14, A24, A34, A44),
    prow4(A11, A12, A13, A14), nl,
    prow4(A21, A22, A23, A24), nl,
    prow4(A31, A32, A33, A34), nl,
    prow4(A41, A42, A43, A44), nl.

prow4(A,B,C,D) :-
    write(A), write(' '), write(B), write(' '), write(C), write(' '), write(D).

perm4(A,B,C,D) :-
    neq4(A,B,C,D),
    num(A), num(B), num(C), num(D).

neq4(A,B,C,D) :-
    neq(A,B), neq(A,C), neq(A,D),
    neq(B,C), neq(B,D),
    neq(C,D).

num(1). num(2). num(3). num(4).

neq(1,2). neq(1,3). neq(1,4).
neq(2,1). neq(2,3). neq(2,4).
neq(3,1). neq(3,2). neq(3,4).
neq(4,1). neq(4,2). neq(4,3).