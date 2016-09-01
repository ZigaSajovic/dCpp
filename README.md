# Operatorska analiza  v Algebri algoritmov

###Povzetek

V tem članku razvijemo teorijo analitičnih strojev, ki implementirajo neskončno-krat odvedljive programske jezike, in operatorjev nad njimi.

  Programski jezik definiramo kot monoid v funkcijskem vektorskem prostoru preslikav nad virtualnim pomnilnikom. Virtualni pomnilnik konstruiramo skozi tenzorsko algebro in ga opremimo s pripadajočo algebro algoritmov. Skozi to algebro konstruiramo diferencialne operatorje, ki nad programskimi jeziki napenjajo prostor neskončno-krat odvedljivih programov. Predstavimo celostno teorijo operatorjev, ki omogoča analizo programov in izračune na nivoju operatorjev samih, kar je seveda naklonjeno splošni implementaciji. Skozi teorijo izpeljemo nove operatorje, ki program razvijejo v neskončne potenčne vrste v algebri algoritmov. Teorijo uporabimo za analizo iteratorjev v programskih jezikih, in njihove odvisnosti od izstopnih pogojev. 
  
  Z razvitim konstruiramo funkcijske transformacije programov v poljubni funkcijski bazi (navadno tisti, ki jo kot optimalno navaja proizvajalec strojne opreme). 
  Tako s teorijo pridobimo nov pristop k analizi programov in sposobnost določanja časovne kompleksnosti algoritmov, z vedenjem reda napak aproksimacije.

Članek je dobra razlaga delovanja knjižnice
https://github.com/ZigaSajovic/dCpp.
