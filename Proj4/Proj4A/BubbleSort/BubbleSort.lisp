(defun bubble-sort (array)
  (let ((n (length array)))
    (loop for i from 0 below (1- n) do
          (loop for j from 0 below (- n i 1) do
                (when (> (aref array j) (aref array (1+ j)))
                  (rotatef (aref array j) (aref array (1+ j))))))
    array))

;; Test the sorting
(let ((array (vector 5 1 4 2 8)))
  (bubble-sort array)
  (print array))
