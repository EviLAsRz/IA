(deftemplate valvula
    (slot nombre (default ""))
    (slot T1 (type INTEGER) (default 0))
    (slot T2 (type INTEGER) (default 0))
    (slot presion (type INTEGER) (default 0))
    (slot estado (default cerrada) (allowed-values abierta cerrada))
);valvulas

(deffacts BasedeDatas
    (valvula (nombre Entrada) (T1 101) (T2 35) (presion 1))
    (valvula (nombre Salida) (T1 101) (T2 155) (presion 5))
    (valvula (nombre Pasillo1) (T1 99) (T2 37) (estado cerrada))
);basedehechos

(deffunction calculo_presion (?p1 ?temp1)
    (while (> ?temp1 35)
        (bind ?p1(+ ?p1 1))
        (bind ?temp1(- ?temp1 5))
    )
    (return ?p1)
);funcion_calculo_presion

(deffunction calculo_temperatura (?t1 ?t2)
    (if (> ?t2 ?t1) then
        (bind ?res (- ?t2 ?t1))
    )
    (return ?res)
);funcion_calculo_temperatura

(defrule R1
    ?v1<-(valvula (nombre ?n) (T1 ?t1) (T2 ?t2) (presion ?p) (estado ?e))
    (test (= ?p 5))
    (test (eq ?e abierta))
    =>
    (modify ?v1 (presion 0) (estado cerrada))
);Regla_r1

(defrule R2
    ?v1<-(valvula (nombre ?n) (T1 ?t1) (T2 ?t2) (presion ?p) (estado ?e))
    (test (> ?t1 35))
    (test (< ?p 10))
    (test (eq ?e cerrada))
    =>
    (modify ?v1 (presion (calculo_presion ?p ?t1)) (estado abierta))
);regla_r2

(defrule R3
    ?v1<-(valvula (nombre ?n1) (T1 ?v1t1) (T2 ?t2) (presion ?p) (estado ?e))
    ?v2<-(valvula (nombre ?n2) (T1 ?v2t1) (T2 ?t2) (presion ?p) (estado ?e))
    (test (neq ?n1 ?n2))
    (test (< ?v2t1 ?t2))
    ;se puede comprobar de antemano que t2 > t1, asi nos ahorramos el if en la funcion del calculo de temp
    =>
    (modify ?v1 (estado abierta))
    (modify ?v2 (T2 (calculo_temperatura ?v2t1 ?t2)) (estado abierta))
);regla_r3

