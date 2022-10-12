(define-module (extra stopwatch)
  #:use-module (system foreign)
  #:use-module (system foreign-library)
  #:export (make-stopwatch
	    start-stopwatch!
	    stop-stopwatch!
	    reset-stopwatch!
	    stopwatch-time
	    stopwatch-running?
	    time-thunk))

(define libstopwatch
  (load-foreign-library "libstopwatch_guile"))

(define-wrapped-pointer-type stopwatch
  stopwatch?
  wrap-stopwatch unwrap-stopwatch
  (lambda (obj port)
    (format port "#<stopwatch ~x>"
	    (pointer-address
	     (unwrap-stopwatch obj)))))

(define-syntax-rule (ffunc c-name args ...)
  (foreign-library-function
   libstopwatch c-name args ...))

(define (make-stopwatch)
  "Returns a new stopwatch."
  (wrap-stopwatch
   ((ffunc "stopwatch_new"
	   #:return-type '*))))

(define-syntax-rule (def-sw scheme-name c-name)
  (define (scheme-name sw)
    ((ffunc c-name #:arg-types '(*))
     (unwrap-stopwatch sw))))

(def-sw start-stopwatch! "stopwatch_start")
(def-sw stop-stopwatch! "stopwatch_stop")
(def-sw reset-stopwatch! "stopwatch_reset")

(define (stopwatch-time sw)
  "Total number of seconds elapsed."
  ((ffunc "stopwatch_time"
	  #:return-type double
	  #:arg-types '(*))
   (unwrap-stopwatch sw)))

(define (as-bool num)
  "Returns Scheme boolean value from an int."
  (if (= num 0) #f #t))

(define (stopwatch-running? sw)
  "Returns #t iff the stopwatch is running."
  (as-bool
   ((ffunc "stopwatch_is_running"
	   #:return-type int
	   #:arg-types '(*))
    (unwrap-stopwatch sw))))

(define (time-thunk thunk)
  "Executes thunk() and times how long it
takes to finish in seconds."
  (let ((sw (make-stopwatch)))
    (dynamic-wind
      (lambda () (start-stopwatch! sw))
      thunk
      (lambda ()
	(stop-stopwatch! sw)))
    (stopwatch-time sw)))
