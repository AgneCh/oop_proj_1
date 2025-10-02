# oop_proj_1


(v0.2)

Atlikus programos spartos testus su skirtingais duomenų failų dydžiais (1 tūkst., 10 tūkst., 100 tūkst., 1 mln. ir 10 mln. įrašų), nustatyta:

- Failų kūrimo laikas auga beveik tiesiškai priklausomai nuo įrašų kiekio.

- Duomenų nuskaitymas užtrunka ilgiau nei kūrimas, ypač su dideliais failais (pvz., 10 mln. įrašų nuskaitymas užtruko vidutiniškai 6,3 s).

Atsitiksinių studentų sąrašų failų kūrimas (vid.):
1 000 įrašų           0.003338122 s
10 000 įrašų          0.010401078 s
100 000 įrašų         0.05856702 s
1 000 000 įrašų       0.4611562 s
10 000 000 įrašų      4.250476 s

Duomenų nuskaitymas iš failų (vid.):
1 000 įrašų           0.002008618 s
10 000 įrašų          0.010693404 s
100 000 įrašų         0.0747804 s
1 000 000 įrašų       0.6019136 s
10 000 000 įrašų      6.308904 s

Studentų rūšiavimas į dvi kategorijas (vid.):
1 000 įrašų           0.000288262 s
10 000 įrašų          0.001714236 s
100 000 įrašų         0.01753584 s
1 000 000 įrašų       0.1313298 s
10 000 000 įrašų      1.46565 s

Surūšiuotų studentų išvedimas į du naujus failus (vid.):
1 000 įrašų           0.000899568 s
10 000 įrašų          0.00393021 s
100 000 įrašų         0.02560846 s
1 000 000 įrašų       0.1830744 s
10 000 000 įrašų      1.760166 s