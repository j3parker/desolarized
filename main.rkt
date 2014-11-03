(module desolarized racket
  (require color-space)
  (provide (struct-out RGB))

  (define-syntax (define-color stx)
    (syntax-case stx ()
      [(_ id val) #'(begin
                      (define id (LAB->RGB val))
                      (provide id))]))

  (define colors '())
  (provide colors)

  (define-syntax (define-color-variants stx)
    (syntax-case stx ()
      [(_ id val)
        (with-syntax
          ([id-light (datum->syntax #'id (string->symbol (format "bright-~a" (syntax->datum #'id))))]
           [id-dark (datum->syntax #'id (string->symbol (format "dark-~a" (syntax->datum #'id))))])
          #`(begin
              (define-color id val)
              (define-color id-light (add-LAB (LAB 25 0 0) val))
              (define-color id-dark (add-LAB (LAB -25 0 0) val)))
          )]))

  (define-color base03 (LAB 10 0 -10))
  (define-color base02 (LAB 25 0 -10))
  (define-color base01 (LAB 50 0 -9))
  (define-color base00 (LAB 60 0 -9))
  (define-color base0 (LAB 75 0 -7))
  (define-color base1 (LAB 85 0 -5))
  (define-color base2 (LAB 95 0 -4))
  (define-color base3 (LAB 101 0 0))

  (define-color-variants yellow (LAB 70 10 65))
  (define-color-variants orange (LAB 65 45 300))
  (define-color-variants red (LAB 50 65 45))
  (define-color-variants magenta (LAB 50 65 -05))
  (define-color-variants violet (LAB 50 15 -45))
  (define-color-variants blue (LAB 55 -10 -45))
  (define-color-variants cyan (LAB 60 -35 -05))
  (define-color-variants green (LAB 60 -25 65))

  (define fg 'not-set)
  (define fg-secondary 'not-set)
  (define bg 'not-set)
  (define bg-secondary 'not-set)
  (define muted 'not-set)

  (define (set-mode mode)
    (cond
      [(equal? mode 'light) (set! fg base03)
                            (set! fg-secondary base00)
                            (set! bg base3)
                            (set! bg-secondary base2)
                            (set! muted base2)]

      [(equal? mode 'dark) (set! fg base0)
                           (set! fg-secondary base01)
                           (set! bg base03)
                           (set! bg-secondary base02)
                           (set! muted base02)]))
  (provide fg fg-secondary bg bg-secondary muted set-mode)

  (define (to-css c) (~a "rgb(" (RGB-r c) ", " (RGB-g c) ", " (RGB-b c) ");"))
  (provide to-css)
)
