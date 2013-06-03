<?php

$str = '


texts[0] = "Mi familia es muy importante en mi vida. Mi familia es italiana, y es muy grande y amorosa. Es bueno que tengo una familia que me ayuda. Mi papá y mi mamá me aman y me ayudan a pagar la escuela y los libros. Es increíble lo mucho que hacen por mí. No es posible que yo estaría muy bien sin ellos. Mi hermano me da consejos sobre la escuela y cómo vivir mi vida. Mi hermano es muy importante para mí. Mi hermana me da consejos sobre la escuela y el trabajo y las relaciones. Ella es muy importante para mí. Mis abuelos me ayudan diciéndome experiencias que tuvieron en su vida. Es importante que estén en mi vida, porque he aprendido muchas lecciones de ellas. Mi padre es la persona más grande que conozco. Él ayuda a mantener mi familia para días feriados y vacaciones. No es posible que yo no puedo hablar con mi padre todos los días. Mi madre también me ama. Ella me ayuda a aprender computación y lecciones de vida de las experiencias. Es increíble que tengo una gran familia en mi vida. Es bueno que me apoyan y me aman sin importar nada.
";

texts[1] = "24 Samizdat
exil nakl 68 Publishers Index
e čsps Svědectví Listy Proměny
sam čsps Vokno Revolver revue
sam edice Petlice Edice expedice
Arnošt Lustig, Jiří Mucha, Vác Černý, Boh Hrabal Perlička na dvě Postřižiny Ostře sled v, Jách Topol Sestra, Ivan Klíma Milenci na jednu noc, Pavel Tigrid svědomí čs národa, Milan Kundera Směšné lásky, Josef Škvorecký Zbabělci, Tankový prapor, Ludvíc Vaculík Jak se dělá chlapec
";

';

$str = trim($str);
$str = str_replace("\n\n\n", '%NEWLINE%', $str);
$str = str_replace("\n", '| ', $str);
$str = str_replace('%NEWLINE%', "\n", $str);
$str = str_replace('š', 's', $str);
$str = str_replace('ř', 'r', $str);
$str = str_replace('ž', 'z', $str);
$str = str_replace('ů', 'u', $str);
$str = str_replace('ň', 'n', $str);
$str = str_replace('-', '--', $str);
$str = str_replace('Š', 'S', $str);
$str = str_replace('Ř', 'R', $str);
$str = str_replace('Ž', 'Z', $str);
$str = str_replace('Ů', 'U', $str);

$file = file_get_contents(__DIR__ . '/src/app_text.c');
$file = preg_replace('~(/\* BEGINTEXT \*/).*(/\* ENDTEXT \*/)~is', "\$1\n$str\n\$2", $file);

file_put_contents(__DIR__ . '/src/app_text.c', $file);
