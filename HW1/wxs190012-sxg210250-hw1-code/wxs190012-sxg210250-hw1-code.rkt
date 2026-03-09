;WXS190012 - Winston Shih - CS 4337.004
;SXG210250 - Satyam Garg - CS 4337.004

#lang racket
;Q5-Start---------------------------------------------------------------------------
; Helping function for main leaves function
; Exactly how it was in the lecture notes
(define (append list1 list2)
  (cond
    ((null? list1) list2)
    (else (cons (car list1) (append (cdr list1) list2)))
  ))
; Main function to find leaves in right-to-left order.
(define (leaves a_tree)
  (cond
    ((null? a_tree) '())
    ((list? (car a_tree))
     (append (leaves (cdr a_tree)) (leaves (car a_tree))))
    (else (append (leaves (cdr a_tree)) (list (car a_tree))))
  ))
;Q5-End-----------------------------------------------------------------------------
;Q6-Start---------------------------------------------------------------------------
(define (last-element l)
  (if (null? (cdr l)) ;If cdr l is not null, the function recurses to cdr l.
      (car l) (last-element (cdr l)))) ;If cdr l is null, then the function returns car l.
;Q6-End-----------------------------------------------------------------------------
;Q7-Start---------------------------------------------------------------------------
;; EXP-DEPTH: depth of the most-nested parentheses inside x
;; (does NOT count the outermost pair around x)
(define (max a b)
  (if (> a b) a b))

;; Your EXP-DEPTH function with max now working
(define (EXP-DEPTH x)
  (if (list? x)
      (cond
        [(null? x) 0]
        [else
         (max (if (list? (car x))
                  (+ 1 (EXP-DEPTH (car x)))
                  0)
              (EXP-DEPTH (cdr x)))])
      0))

;Q7-End-----------------------------------------------------------------------------
;Q8-Start---------------------------------------------------------------------------
(define (newlist lst)
  (cond
    ((null? lst) '()) ;Base cae 1: If list is empty, return '()
    ((null? (cdr lst)) lst) ; Base case 2: If list has only one element, then the list is returned as is.
    (else (cons (cadr lst) (cons (car lst) (newlist (cddr lst))))))) ;Else, The function adds second element then first element before another recursion.
;Q8-End-----------------------------------------------------------------------------
;Q9-Start---------------------------------------------------------------------------
;; true if d divides n (no remainder), implemented by repeated subtraction
(define (divides? d n)
  (cond
    ((< n d) #f)
    ((= n d) #t)
    (else (divides? d (- n d)))))
;; true if n has any divisor in [d .. n-1]
(define (has-divisor? n d)
  (cond
    ((= d n) #f)
    ((divides? d n) #t)
    (else (has-divisor? n (+ d 1)))))
;; true if n is prime (n >= 2 and no divisor starting at 2)
(define (prime? n)
  (cond
    ((< n 2) #f)
    (else (not (has-divisor? n 2)))))
;; append a single element x to the end of list xs
(define (append1 xs x)
  (cond
    ((null? xs) (cons x '()))
    (else (cons (car xs) (append1 (cdr xs) x)))))
;; list of all primes <= n, in ascending order
(define (primes-up-to n)
  (cond
    ((< n 2) '())
    ((prime? n) (append1 (primes-up-to (- n 1)) n))
    (else (primes-up-to (- n 1)))))
;Q9-End-----------------------------------------------------------------------------
;Q10-Start--------------------------------------------------------------------------
;Method to find all whole numbers from start to end.
(define (numbers-between start end)
  (define (push current list)
    (cond
      ((= current end) (reverse list))
      (else (push (+ current 1) (cons current list)))))
  (push (+ start 1) '()))
;Method to reverse the contents of a list.
(define (reverse l)
  (if (empty? l)
      '()
      (append (reverse (cdr l)) (list (car l)))))
;Method to append two lists together.
(define (appends l1 l2)
  (cond
    ((null? l1) l2)
    (else (cons (car l1) (appends (cdr l1) l2)))
   ))
;Q10-End----------------------------------------------------------------------------
;Output-lines-Start-----------------------------------------------------------------
;Q5
(leaves '((1 2)(3 4 5)((6))7))
;Q6
(last-element '(a (b c) () (d e)) )
;Q7
(EXP-DEPTH ' ( ( (A B ((C)) ()) D) E))
;Q8
(newlist '( () a (b) (c d) f))
;Q9
(primes-up-to '7)
;Q10
(numbers-between '-3 '3)
;Output-lines-End-------------------------------------------------------------------