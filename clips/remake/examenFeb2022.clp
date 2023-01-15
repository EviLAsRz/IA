(deftemplate personal
(slot dni (type INTEGER))
(slot nombre)
(slot turno (allowed-values manana tarde ambos))
(slot total_ventas)
(slot encargado (allowed-values SI NO))
)

(deftemplate producto
(slot id (type INTEGER))
(slot nombre)
(slot stock_cafe)
(slot stock_alma)
(slot precio)
(slot máximo (default 30))
)

(deftemplate venta
(slot camarero)
(slot producto)
(slot unidades)
(slot pago (allowed-values tarjeta efectivo bono))
)

    ;(venta (camarero Juan) (producto cafe) (unidades 2) (pago tarjeta))
    ;(personal (dni 1234) (nombre Juan) (turno manana) (total_ventas 5) (encargado SI))
    ;(producto (id 1) (nombre cafe) (stock_cafe 10) (stock_alma 20) (precio 1))

(defrule asignarVenta
    ?v<-(venta (camarero ?nom) (producto ?prod) (unidades ?unid) (pago ?pag))
    ?per<-(personal (dni ?dni) (nombre ?nom) (total_ventas ?tot))
    ?producto<-(producto (id ?id) (nombre ?prod) (stock_cafe ?stock_c) (stock_alma ?stock_a) (precio ?prec))
    (test (>= ?stock_c ?unid))
    =>
    (modify ?per (total_ventas (+ ?tot 1)))
    (modify ?producto (stock_cafe (- ?stock_c ?unid)))
    (bind ?coste (* ?prec ?unid))
    (printout t ?nom": "?unid" unidades de "?prod", "?coste" euros pagados con "?pag"." crlf)
)