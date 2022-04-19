(deftemplate aeronave
    (slot idnave)
    (slot compania)
    (slot origen)
    (slot destino)
    (slot velocidadactual)
    (slot peticion (allowed-values Ninguna Despegue Aterrizaje Emergencia Rumbo))
    (slot estado (default enTierra) (allowed-values enTierra Ascenso Crucero Descenso))
);Aeronaves

(deftemplate aerodromo
    (slot idaerodromo)
    (slot ciudad)
    (slot estado (allowed-values ON OFF))
    (slot radiovisibilidad)
    (slot velocidadviento)

);Aerodromos

(deftemplate piloto
    (slot idnave)
    (slot estado (allowed-values OK SOS Ejecutando Stand-by) (default Stand-by))
);Pilotos

(deftemplate vuelo
    (slot idaerodromo1)
    (slot idaerodromo2)
    (slot distancia)
    (slot velocidaddespegue (default 240))
    (slot velocidadcrucero (default 700))
);Vuelos


(defrule Despegar
    ?anave<-(aeronave (idnave ?idn) (compania ?nc) (estado enTierra) (origen ?ornave) (destino ?desnave))
    ?adromo1<-(aerodromo (idaerodromo ?id1)(ciudad ?cdromo1) (estado ON) (radiovisibilidad ?rv) (velocidadviento ?vv))
    ?adromo2<-(aerodromo (idaerodromo ?id2)(ciudad ?cdromo2))
    ?p<-(piloto (idnave ?idn) (estado OK))
    ?v<-(vuelo (idaerodromo1 ?id1) (idaerodromo2 ?id2) (velocidaddespegue ?vdes))
    (test (<> ?id1 ?id2)) ;distinto aerodromo
    (test (eq ?ornave ?cdromo1)) ;origen nave = ciudad aerodromo despegue
    (test (eq ?desnave ?cdromo2)) ;destino nave = ciudad aerodromo destino
    (test (> ?rv 5)) ;radio visibilidad > 5 km/h
    (test (< ?vv 75)) ;velocidad viento < 75 km/h
    =>
    (modify ?p (estado Ejecutando)) ;estado Ejecutando
    (modify ?anave (estado Ascenso) (velocidadactual ?vdes) (peticion Ninguna)) ;estado ascenso, velocidad de despegue, peticion Ninguna
);Regla Despegar

(defrule Excepcion
    ?p<-(piloto (idnave ?idn) (estado ?esp))
    ?anave<-(aeronave (idnave ?idn) (compania ?nc) (origen ?ornave) (destino ?desnave) (peticion Despegue))
    ?adromo1<-(aerodromo (idaerodromo ?id1)(ciudad ?cdromo1) (estado ON) (radiovisibilidad ?rv) (velocidadviento ?vv))
    ?adromo2<-(aerodromo (idaerodromo ?id2)(ciudad ?cdromo2))
    (test (neq ?esp OK)) ;estado piloto <> OK
    (test (<> ?id1 ?id2)) ;distinto aerodromo
    (test (eq ?ornave ?cdromo1)) ;origen nave = ciudad aerodromo despegue
    (test (eq ?desnave ?cdromo2)) ;destino nave = ciudad aerodromo destino
    =>
    (modify ?anave (peticion Emergencia))
    (printout t "ATENCION El piloto de la aeronave "?idn" de la compañia "?nc
    "no se encuentra disponible para realizar el despuegue desde el aerodromo "?cdromo1" con destino "?cdromo2"." crlf)
);Regla excepcion


