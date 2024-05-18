ls6x6(A11,A12,A13,A14,A15,A16,
      A21,A22,A23,A24,A25,A26,
      A31,A32,A33,A34,A35,A36,
      A41,A42,A43,A44,A45,A46,
      A51,A52,A53,A54,A55,A56,
      A61,A62,A63,A64,A65,A66) :-
    perm6(A11,A12,A13,A14,A15,A16),
    perm6(A21,A22,A23,A24,A25,A26),
    perm6(A31,A32,A33,A34,A35,A36),
    perm6(A41,A42,A43,A44,A45,A46),
    perm6(A51,A52,A53,A54,A55,A56),
    perm6(A61,A62,A63,A64,A65,A66),
    perm6(A11,A21,A31,A41,A51,A61),
    perm6(A12,A22,A32,A42,A52,A62),
    perm6(A13,A23,A33,A43,A53,A63),
    perm6(A14,A24,A34,A44,A54,A64),
    perm6(A15,A25,A35,A45,A55,A65),
    perm6(A16,A26,A36,A46,A56,A66),
    prow6(A11,A12,A13,A14,A15,A16), nl,
    prow6(A21,A22,A23,A24,A25,A26), nl,
    prow6(A31,A32,A33,A34,A35,A36), nl,
    prow6(A41,A42,A43,A44,A45,A46), nl,
    prow6(A51,A52,A53,A54,A55,A56), nl,
    prow6(A61,A62,A63,A64,A65,A66), nl.

prow6(A,B,C,D,E,F) :-
    write(A), write(' '), write(B), write(' '), write(C), write(' '),
    write(D), write(' '), write(E), write(' '), write(F).

perm6(A,B,C,D,E,F) :-
    neq6(A, B, C, D, E, F),
    num(A), num(B), num(C), num(D), num(E), num(F).

neq6(A,B,C,D,E,F) :-
    neq(A,B), neq(A,C), neq(A,D), neq(A,E), neq(A,F),
    neq(B,C), neq(B,D), neq(B,E), neq(B,F),
    neq(C,D), neq(C,E), neq(C,F),
    neq(D,E), neq(D,F),
    neq(E,F).

num(1). num(2). num(3). num(4). num(5). num(6).

neq(1,2). neq(1,3). neq(1,4). neq(1,5). neq(1,6).
neq(2,1). neq(2,3). neq(2,4). neq(2,5). neq(2,6).
neq(3,1). neq(3,2). neq(3,4). neq(3,5). neq(3,6).
neq(4,1). neq(4,2). neq(4,3). neq(4,5). neq(4,6).
neq(5,1). neq(5,2). neq(5,3). neq(5,4). neq(5,6).
neq(6,1). neq(6,2). neq(6,3). neq(6,4). neq(6,5).
