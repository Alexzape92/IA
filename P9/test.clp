(deffacts iniciales
    (ubicacion A norte D)
    (ubicacion A oeste B)
    (ubicacion B norte E)
    (ubicacion B oeste C)
    (ubicacion C norte F)
    (ubicacion D norte G)
    (ubicacion D oeste E)
    (ubicacion E norte H)
    (ubicacion E oeste F)
    (ubicacion F norte I)
    (ubicacion G oeste H)
    (ubicacion H oeste I)
);

(defrule inversas_sur
    (ubicacion ?x norte ?y)
    =>
    (assert(ubicacion ?y sur ?x))
);

(defrule inversas_este
    (ubicacion ?x oeste ?y)
    =>
    (assert(ubicacion ?y este ?x))
);

(defrule transitivas
    (ubicacion ?x ?posi ?y)
    (ubicacion ?y ?posi ?z)
    =>
    (assert(ubicacion ?x ?posi ?z))
);

(defrule noroeste
    (ubicacion ?x norte ?y)
    (ubicacion ?y oeste ?z)
    =>
    (assert(ubicacion ?x noroeste ?z))
);

(defrule noreste
    (ubicacion ?x norte ?y)
    (ubicacion ?y este ?z)
    =>
    (assert(ubicacion ?x noreste ?z))
);

(defrule suroeste
    (ubicacion ?x sur ?y)
    (ubicacion ?y oeste ?z)
    =>
    (assert(ubicacion ?x suroeste ?z))
);

(defrule sureste
    (ubicacion ?x sur ?y)
    (ubicacion ?y este ?z)
    =>
    (assert(ubicacion ?x sureste ?z))
);

(defrule inicio
?f1 <-(situacion ?x ?y)
(ubicacion ?x ?u ?y)
=>
(printout t ?x " esta al " ?u " de " ?y crlf)
(retract ?f1)
);; inicio