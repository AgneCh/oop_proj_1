# oop_proj_1


# (v0.3)
Šioje versijoje (`v0.3`) buvo atliktas testavimas, siekiant palyginti `std::vector` ir `std::list` veikimo spartą.
Testavimui naudoti tie patys duomenų failai kaip ir `v0.2` versijoje.  
Kiekvienam konteineriui buvo atliekami matavimai su tokiais įrašų kiekiais (1000, 10000, 100000, 1000000, 10000000 įrašų).

## Testavimo aplinka
| Parametras |  Reikšmė                    | 
|------------|-----------------------------|
| CPU        | Intel(R) Core(TM) i7-1065G7 |
| RAM        | 8 GB                        |
| Diskas     | SSD                         |
| OS         | Ubuntu 24.04.3 LTS          |


## Rezultatai

# Atsitiksinių studentų sąrašų failų kūrimas (vid.)
| Įrašų kiekis | `std::vector` (s) | `std::list` (s) |
|--------------|-------------------|----------------|
| 1 000        | 0.0017713         | 0.001936278
| 10 000       | 0.00814588        | 0.0110534
| 100 000      | 0.05982952        | 0.06057134
| 1 000 000    | 0.4506244         | 0.4379546
| 10 000 000   | 4.3473            | 4.343814


# Duomenų nuskaitymas iš failų (vid.)
| Įrašų kiekis | `std::vector` (s) | `std::list` (s) |
|--------------|-------------------|----------------|
| 1 000        | 0.002358702       | 0.001804468
| 10 000       | 0.01968436        | 0.01750358
| 100 000      | 0.08291886        | 0.078372
| 1 000 000    | 0.6835998         | 0.561991
| 10 000 000   | 6.60041           | 6.604486


# Studentų rūšiavimas į dvi kategorijas (vid.)
| Įrašų kiekis | `std::vector` (s) | `std::list` (s) |
|--------------|-------------------|----------------|
| 1 000        | 0.000294958       | 0.000172689
| 10 000       | 0.002069002       | 0.00192168
| 100 000      | 0.01242656        | 0.01240088
| 1 000 000    | 0.1211802         | 0.10524554
| 10 000 000   | 1.192148          | 1.1188372


# Surūšiuotų studentų išvedimas į du naujus failus (vid.)
| Įrašų kiekis | `std::vector` (s) | `std::list` (s) |
|--------------|-------------------|----------------|
| 1 000        | 0.002195244       | 0.00879666
| 10 000       | 0.0164007         | 0.01603442
| 100 000      | 0.05875878        | 0.07475656
| 1 000 000    | 0.5272746         | 0.6350894
| 10 000 000   | 4.934834          | 5.80888




# (v0.2)

Atlikus programos spartos testus su skirtingais duomenų failų dydžiais (1 tūkst., 10 tūkst., 100 tūkst., 1 mln. ir 10 mln. įrašų), nustatyta:

- Failų kūrimo laikas auga beveik tiesiškai priklausomai nuo įrašų kiekio.

- Duomenų nuskaitymas užtrunka ilgiau nei kūrimas, ypač su dideliais failais (pvz., 10 mln. įrašų nuskaitymas užtruko vidutiniškai 6,3 s).

| Įrašų kiekis     | Atsitiksinių studentų sąrašų failų kūrimas (vid.) |
|------------------|---------------------------------------------------|
| 1 000 įrašų      |    0.003338122 s
| 10 000 įrašų     |    0.010401078 s
| 100 000 įrašų    |    0.05856702 s
| 1 000 000 įrašų  |    0.4611562 s
| 10 000 000 įrašų |    4.250476 s

| Įrašų kiekis     | Duomenų nuskaitymas iš failų (vid.) |
|------------------|-------------------------------------|
| 1 000 įrašų      |     0.002008618 s
| 10 000 įrašų     |     0.010693404 s
| 100 000 įrašų    |     0.0747804 s
| 1 000 000 įrašų  |     0.6019136 s
| 10 000 000 įrašų |     6.308904 s

| Įrašų kiekis     |Studentų rūšiavimas į dvi kategorijas (vid.) |
|------------------|---------------------------------------------|
| 1 000 įrašų      |     0.000288262 s
| 10 000 įrašų     |     0.001714236 s
| 100 000 įrašų    |     0.01753584 s
| 1 000 000 įrašų  |     0.1313298 s
| 10 000 000 įrašų |     1.46565 s

| Įrašų kiekis     |Surūšiuotų studentų išvedimas į du naujus failus (vid.) |
|------------------|--------------------------------------------------------|
| 1 000 įrašų      |     0.001948826 s
| 10 000 įrašų     |     0.013065428 s
| 100 000 įrašų    |     0.06703692 s
| 1 000 000 įrašų  |     0.5017516 s
| 10 000 000 įrašų |     4.878024 s