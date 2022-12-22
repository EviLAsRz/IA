(deftemplate valvula
    (slot nombre)
    (slot T1 (default 0))
    (slot T2 (default 0))
    (slot presion (default 0))
    (slot estado (allowed-values abierta cerrada) (default cerrada))
)

(deffacts BasedeHechos
    (valvula (nombre Entrada) (T1 101) (T2 35) (presion 1))
    (valvula (nombre Salida) (T1 101) (T2 155) (presion 5))
    (valvula (nombre Pasillo1) (T1 99) (T2 37) (estado cerrada))
)

(deffunction aumentarPresion (?presion ?temp1)
    (while (> ?temp1 35)
        (bind ?presion (+ ?presion 1))
        (bind ?temp1 (- ?temp1 5))
    )
    (return ?presion)
)

(deffunction decrementarTemperatura (?t1 ?t2)
    (if (> ?t1 ?t2) then
        (bind ?res (- ?t1 ?t2))
    )else
        (bind ?res (- ?t2 ?t1))

    (return ?res)
)

(defrule R1
    ?v <- (valvula (presion ?p))
    (test (= ?p 5))
    =>
    (modify ?v (presion 0) (estado cerrada))
)

(defrule R2
    ?v <- (valvula (presion ?p) (T1 ?t1) (estado ?e))
    (test (< ?p 10))
    (test (> ?t1 35))
    (test (eq ?e cerrada))
    =>
    (modify ?v (presion (aumentarPresion ?p ?t1)) (estado abierta))
)

(defrule R3
    ?v1 <- (valvula (nombre ?n1) (presion ?p1) (T1 ?t1v1) (T2 ?t2) (estado ?e1))
    ?v2 <- (valvula (nombre ?n2) (presion ?p2) (T1 ?t1v2) (T2 ?t2) (estado ?e2))
    (test (neq ?n1 ?n2))
    (test (< ?t1v2 ?t2))
    =>
    (modify ?v1 (estado abierta))
    (modify ?v2 (T2 (decrementarTemperatura ?t1v2 ?t2)) (estado abierta))
    
)