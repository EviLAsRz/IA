(deftemplate usuario
    (slot DNI)
    (slot Pin)
    (slot Cantidad (default 0))
);Usuario

(deftemplate tarjeta
    (slot DNI)
    (slot Pin)
    (slot Intentos (default 3))
    (slot Limite (default 400))
    (slot Anno (default 2022))
    (slot Valido(allowed-values Si No) (default Si))
);Tarjeta

(deftemplate cuenta
    (slot DNI)
    (slot Saldo)
    (slot Estado (allowed-values enPantalla dineroEntregado SuperaLimite SinSaldo Inicial)
        (default Inicial))
);Cuenta

(deffacts BasedeHechos
    (usuario (DNI 123456) (Pin 1212) (Cantidad 300))
    (usuario (DNI 456456) (Pin 1211) (Cantidad 200))
    (usuario (DNI 456456) (Pin 4545) (Cantidad 3000))
    (tarjeta (DNI 123456) (Pin 1212) (Intentos 3) (Limite 500) (Anno 2022))
    (tarjeta (DNI 456456) (Pin 4545) (Intentos 3) (Limite 500) (Anno 2022))
    (tarjeta (DNI 000111) (Pin 0011) (Intentos 0) (Limite 500) (Anno 2022))
    (cuenta (DNI 123456) (Saldo 5000))
    (cuenta (DNI 456456) (Saldo 33))
    (cuenta (DNI 000111) (Saldo 30000))
);Hechos

(defglobal ?*limite1* = 900)
(defglobal ?*ANNO* = 2020)

(deffunction decrementar_valor (?x)
    (bind ?x(- ?x 1))
    return ?x
);decrementa en 1

(deffunction diferencia (?x ?y)
    (if(> ?x ?y) then
        (bind ?res(- ?x ?y))
    else
        (bind ?res(- ?y ?x))
)
    return ?res
);diferencia entre dos valores

(defrule Supera_Intentos
    (declare (salience 1))
    ?t<-(tarjeta (Pin ?p) (DNI ?dni) (Intentos ?i) (Limite ?l) (Anno ?a) (Valido ?v))
    (test (<= ?i 0))
    =>
    (printout t "Se ha superado el limite de los intentos de la tarjeta con ID: "?dni"." crlf)
    (retract ?t)
);Supera_Intentos (solo entra tarjeta con intentos = 0)

(defrule Pin_Invalido
    (declare (salience 1))
    (usuario (DNI ?dni) (Pin ?p1) (Cantidad ?c))
    ?t<-(tarjeta (Pin ?p2) (DNI ?dni) (Intentos ?i) (Limite ?l) (Anno ?a) (Valido ?v))
    (test (neq ?p1 ?p2))
    =>
    (modify ?t(Intentos (decrementar_valor ?i)))
    (printout t "La tarjeta con ID: "?dni" no esta validada. (intentos restantes: " ?i")" crlf)
);Pin_Invalido (solo entra usuario y tarjeta con mismo dni)

(defrule Valida_Tarjeta
    (declare (salience 1))
    (usuario (DNI ?dni) (Pin ?p) (Cantidad ?c))
    ?t<-(tarjeta (Pin ?p) (DNI ?dni) (Intentos ?i) (Limite ?l) (Anno ?a) (Valido ?v))
    (test (>= ?i 0))
    (test (>= ?a ?*ANNO*))
    =>
    (printout t "Tarjeta con ID: "?dni" validada" crlf)
);Valida_Tarjeta (solo entra tarjeta con mismo dni y pin que usuario)

(defrule Muestra_Saldo
    (tarjeta (Pin ?p) (DNI ?dni) (Intentos ?i) (Limite ?l) (Anno ?a) (Valido ?v))
    ?c<-(cuenta (DNI ?dni) (Saldo ?s) (Estado ?e))
    (test (eq ?v Si))
    (test (neq ?e enPantalla))
    =>
    (modify ?c (Estado enPantalla))
    (printout t "Saldo de la Cuenta "?dni ": " ?s crlf)
);Muestra_Saldo

(defrule Saldo_NoSuficiente
    (declare (salience 1))
    (cuenta (DNI ?dni) (Saldo ?s) (Estado ?e))
    (test (= ?s 0))
    =>
    (printout t "La cuenta "?dni" no tiene saldo disponible." crlf)
);Saldo_NoSuficiente

(defrule Comprueba_Limite1
    (declare (salience 1))
    ?u<-(usuario (DNI ?dni) (Pin ?p) (Cantidad ?c))
    (test (> ?c ?*limite1*))
    =>
    (printout t "Usuario"?dni" ha superado el limite de saldo a retirar." crlf)
    (retract ?u)
);Comprueba_Limite1

(defrule Comprueba_Limite2
    (declare (salience 1))
    ?u<-(usuario (DNI ?dni) (Pin ?p) (Cantidad ?c))
    (tarjeta (Pin ?p) (DNI ?dni) (Intentos ?i) (Limite ?l) (Anno ?a) (Valido ?v))
    (test (> ?c ?l))
    =>
    (printout t "Usuario"?dni" ha superado el limite de saldo a retirar utilizando la tarjeta." crlf)
    (retract ?u)
);Comprueba_Limite2

(defrule Entrega_Dinero
    ?u<-(usuario (DNI ?dni) (Pin ?p) (Cantidad ?c))
    ?t<-(tarjeta (Pin ?p) (DNI ?dni) (Intentos ?i) (Limite ?l) (Anno ?a) (Valido ?v))
    ?cu<-(cuenta (DNI ?dni) (Saldo ?s) (Estado ?e))
    (test (>= ?s ?c))
    (test (<= ?c ?l))
    =>
    (modify ?cu (Saldo (diferencia ?s ?c))(Estado dineroEntregado))
    (modify ?u (Cantidad 0))
    (retract ?u)
    (printout t "Dinero entregado."crlf"Saldo restante de la cuenta "?dni": "?s crlf)
);Entrega_Dinero








