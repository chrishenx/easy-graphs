/**
 
 -- This code is an usage example of the easy-graph library --
 
 The Mexico City metro network, you can test it with the dfs, bfs and dijkstra algorithms
  
 */

#include <iostream>
#include "../include/graph.h"
#include "../include/tools/dot_extencion.h"

using namespace std;
using namespace easy_graphs;

Graph<string> create_net();

int main() 
{
  cout << "\nCreating graph" << endl;
  Graph<string> red = create_net();
  cout << "Rendering graph with graphviz..." << endl;
  dotRepr2PNG(red.dotRepr(), "metro", "images");
  const string source = "Chapultepec"; 
  cout << "Computing min-expansing tree from " << source << endl;
  auto min_expansion_tree = red.prim(source);
  cout << "done!" << endl;
  cout << "Rendering min-expansing tree graph with graphviz..." << endl;
  dotRepr2PNG(min_expansion_tree.dotRepr(), "red_prim", "images");
  cout << "done!" << endl;
  return 0;
}

Graph<string> create_net() {
  Graph<string> red(false, false, {"Observatorio", "Tacubaya", "Juanacatlan", "Chapultepec", "Sevilla", "Insurgentes", "Cuauhtemoc", 
     "Balderas", "Salto del Agua", "Isabel la Catolica", "Pino Suarez", "Merced", "Candelaria", "San Lazaro", 
     "Moctezuma", "Balbuena", "Blvd. Puerto Aereo", "Gomez Farias", "Zaragoza", "Pantitlan", //Fin linea 1
     "Cuatro caminos", "Panteones", "Tacuba", "Cuitlahuac", "Popotla", "Colegio Militar", 
     "Normal", "San Cosme", "Revolucion", "Hidalgo", "Bellas Artes", "Allende", "Zocalo", "San Antonio Abad", 
     "Chabacano", "Viaducto", "Xola", "Villa de Cortes", "Nativitas", "Portales", "Ermita", "General Anaya", "Tasquenya", // Fin linea 2
     "Indios Verdes", "Deportivo 18 de marzo", "Potrero", "La Raza", "Tlatelolco", "Guerrero", 
     "Juarez", "Balderas", "Ninyos Heroes", "Hospital General", "Centro Medico", "Etiopia", "Eugenia", 
     "Division del Norte", "Zapata", "Coyoacan", "Viveros", "Miguel A. de Quevedo", "Copilco", "Universidad", // Fin linea 3
     "Martin Carrera", "Talisman", "Bondojito", "Consulado", "Canal del Norte", "Morelos", "Fray Servando", "Jamaica", "Santa Anita", // Fin linea 4
     "Politecnico", "Instituto del Petroleo", "Autobuses del Norte", "Misterios", "Valle Gomez", "Eduardo Molina", 
     "Aragon", "Oceania", "Terminal Aerea", "Hangares", // Fin linea 5
     "El Rosario", "Tezozomoc", "Azcapotzalco", "Ferreria", "Norte 45", "Vallejo", "Lindavista", "La Villa-Basilica", // Fin linea 6
     "Aquiles Serdan", "Camarones", "Refineria", "San Joaquin", "Polanco", "Auditorio", "Constituyentes", 
     "San Pedro de los Pinos", "San Antonio", "Mixcoac", "Barranca del Muerto", // Fin linea 7
     "Garibaldi", "San Juan de Letran", "Doctores", "Obrera", "La Viga", "Coyuya", "Iztacalco", "Apatlaco", 
     "Aculco", "Escuadron 201", "Atlalilco", "Iztapalapa", "Cerro de la Estrella", "UAM-I", "Constitucion de 1917", // Fin linea 8
     "Patriotismo", "Chilpancingo", "Lazaro Cardenas", "Mixiuhca", "Velodromo", "Ciudad Deportiva", "Puebla", // Fin linea 9
     "Tlahuac", "Tlaltenco", "Zapotitlan", "Nopalera", "Olivos", "Tezonco", "Periferico Oriente", "Calle 11", 
     "Lomas Estrella", "San Andres Tomatlan", "Culhuacan", "Mexicaltzingo", "Eje Central", "Parque de los Venados", 
     "Hospital 20 de noviembre", "Insurgentes Sur", // Fin linea 12
     "Agricola Oriental", "Canal de San Juan", "Tepalcates", "Guelatao", "Penion Viejo", "Acatitla", 
     "Santa Marta", "Los Reyes", "La Paz", // Fin linea A
     "Buenavista", "Lagunilla", "Tepito", "Flores Magon", "Romero Rubio", "Deportivo Oceania", "Bosque de Aragon", 
     "Villa de Aragon", "Nezahualcoyotl", "Impulsora", "Rio de los Remedios", "Muzquiz", "Ecatepec", "Olimpica", 
     "Plaza Aragon", "Ciudad Azteca" // Fin linea B
  });

  // linea 1
  red.newEdge("Observatorio", "Tacubaya");
  red.newEdge("Tacuba", "Juanacatlan");
  red.newEdge("Juanacatlan", "Chapultepec");
  red.newEdge("Chapultepec", "Sevilla");
  red.newEdge("Sevilla", "Insurgentes");
  red.newEdge("Insurgentes", "Cuauhtemoc");
  red.newEdge("Cuauhtemoc", "Balderas");
  red.newEdge("Balderas", "Salto del Agua");
  red.newEdge("Salto del Agua", "Isabel la Catolica");
  red.newEdge("Isabel la Catolica", "Pino Suarez");
  red.newEdge("Pino Suarez", "Merced");
  red.newEdge("Merced", "Candelaria");
  red.newEdge("Candelaria", "San Lazaro");
  red.newEdge("San Lazaro", "Moctezuma");
  red.newEdge("Moctezuma", "Balbuena");
  red.newEdge("Balbuena", "Blvd. Puerto Aereo");
  red.newEdge("Blvd. Puerto Aereo", "Gomez Farias");
  red.newEdge("Gomez Farias", "Zaragoza");
  red.newEdge("Zaragoza", "Pantitlan");
  // Linea 2
  red.newEdge("Cuatro caminos", "Panteones");
  red.newEdge("Panteones", "Tacuba");
  red.newEdge("Tacuba", "Cuitlahuac");
  red.newEdge("Cuitlahuac", "Popotla");
  red.newEdge("Popotla", "Colegio Militar");
  red.newEdge("Colegio Militar", "Normal");
  red.newEdge("Normal", "San Cosme");
  red.newEdge("San Cosme", "Revolucion");
  red.newEdge("Revolucion", "Hidalgo");
  red.newEdge("Hidalgo", "Bellas Artes");
  red.newEdge("Bellas Artes", "Allende");
  red.newEdge("Allende", "Zocalo");
  red.newEdge("Zocalo", "Pino Suarez");
  red.newEdge("Pino Suarez", "San Antonio Abad");
  red.newEdge("San Antonio Abad", "Chabacano");
  red.newEdge("Chabacano", "Viaducto");
  red.newEdge("Viaducto", "Xola");
  red.newEdge("Xola", "Villa de Cortes");
  red.newEdge("Villa de Cortes", "Nativitas");
  red.newEdge("Nativitas", "Portales");
  red.newEdge("Portales", "Ermita");
  red.newEdge("Ermita", "General Anaya");
  red.newEdge("General Anaya", "Tasquenya");
  // Linea 3
  red.newEdge("Universidad", "Copilco");
  red.newEdge("Copilco", "Miguel A. de Quevedo");
  red.newEdge("Miguel A. de Quevedo", "Viveros");
  red.newEdge("Viveros", "Coyoacan");
  red.newEdge("Coyoacan", "Zapata");
  red.newEdge("Zapata", "Division del Norte");
  red.newEdge("Division del Norte", "Eugenia");
  red.newEdge("Eugenia", "Etiopia");
  red.newEdge("Etiopia", "Centro Medico");
  red.newEdge("Centro Medico", "Hospital General");
  red.newEdge("Hospital General", "Ninyos Heroes");
  red.newEdge("Ninyos Heroes", "Balderas");
  red.newEdge("Balderas", "Juarez");
  red.newEdge("Juarez", "Hidalgo");
  red.newEdge("Hidalgo", "Guerrero");
  red.newEdge("Guerrero", "Tlatelolco");
  red.newEdge("Tlatelolco", "La Raza");
  red.newEdge("La Raza", "Potrero");
  red.newEdge("Potrero", "Deportivo 18 de marzo");
  red.newEdge("Deportivo 18 de marzo", "Indios Verdes");
  // Linea 4
  red.newEdge("Martin Carrera", "Talisman");
  red.newEdge("Talisman", "Bondojito");
  red.newEdge("Bondojito", "Consulado");
  red.newEdge("Consulado", "Canal del Norte");
  red.newEdge("Canal del Norte", "Morelos");
  red.newEdge("Morelos", "Candelaria");
  red.newEdge("Candelaria", "Fray Servando");
  red.newEdge("Fray Servando", "Jamaica");
  red.newEdge("Jamaica", "Santa Anita");
  // Linea 5
  red.newEdge("Politecnico", "Instituto del Petroleo");
  red.newEdge("Instituto del Petroleo", "Autobuses del Norte");
  red.newEdge("Autobuses del Norte", "La Raza");
  red.newEdge("La Raza", "Misterios");
  red.newEdge("Misterios", "Valle Gomez");
  red.newEdge("Valle Gomez  ", "Consulado");
  red.newEdge("Consulado", "Eduardo Molina");
  red.newEdge("Eduardo Molina", "Aragon");
  red.newEdge("Aragon", "Oceania");
  red.newEdge("Oceania", "Terminal Aerea");
  red.newEdge("Terminal Aerea", "Hangares");
  red.newEdge("Hangares", "Pantitlan");
  // Linea 6
  red.newEdge("El Rosario", "Tezozomoc");
  red.newEdge("Tezozomoc", "Azcapotzalco");
  red.newEdge("Azcapotzalco", "Ferreria");
  red.newEdge("Ferreria", "Norte 45");
  red.newEdge("Norte 45", "Vallejo");
  red.newEdge("Vallejo", "Instituto del Petroleo");
  red.newEdge("Instituto del Petroleo", "Lindavista");
  red.newEdge("Lindavista", "Deportivo 18 de marzo");
  red.newEdge("Deportivo 18 de marzo", "La Villa-Basilica");
  red.newEdge("La Villa-Basilica", "Martin Carrera");
  // Linea 7
  red.newEdge("El Rosario", "Aquiles Serdan");
  red.newEdge("Aquiles Serdan", "Camarones");
  red.newEdge("Camarones", "Refineria");
  red.newEdge("Refineria", "Tacuba");
  red.newEdge("Tacuba", "San Joaquin");
  red.newEdge("San Joaquin", "Polanco");
  red.newEdge("Polanco", "Auditorio");
  red.newEdge("Auditorio", "Constituyentes");
  red.newEdge("Constituyentes", "Tacubaya");
  red.newEdge("Tacubaya", "San Pedro de los Pinos");
  red.newEdge("San Pedro de los Pinos", "San Antonio");
  red.newEdge("San Antonio", "Mixcoac");
  red.newEdge("Mixcoac", "Barranca del Muerto");
  // Linea 8
  red.newEdge("Garibaldi", "Bellas Artes");
  red.newEdge("Bellas Artes", "San Juan de Letran");
  red.newEdge("San Juan de Letran", "Salto del Agua");
  red.newEdge("Salto del Agua", "Doctores");
  red.newEdge("Doctores", "Obrera");
  red.newEdge("Obrera", "Chabacano");
  red.newEdge("Chabacano", "La Viga");
  red.newEdge("La Viga", "Santa Anita");
  red.newEdge("Santa Anita", "Coyuya");
  red.newEdge("Coyuya", "Iztacalco");
  red.newEdge("Iztacalco", "Apatlaco");
  red.newEdge("Apatlaco", "Aculco");
  red.newEdge("Aculco", "Escuadron 201");
  red.newEdge("Escuadron 201", "Iztapalapa");
  red.newEdge("Iztapalapa", "Cerro de la Estrella");
  red.newEdge("Cerro de la Estrella", "UAM-I");
  red.newEdge("UAM-I", "Constitucion de 1917");
  // Linea 9
  red.newEdge("Tacubaya", "Patriotismo");
  red.newEdge("Patriotismo", "Chilpancingo");
  red.newEdge("Chilpancingo", "Centro Medico");
  red.newEdge("Centro Medico", "Lazaro Cardenas");
  red.newEdge("Lazaro Cardenas", "Chabacano");
  red.newEdge("Chabacano", "Jamaica");
  red.newEdge("Jamaica", "Mixiuhca");
  red.newEdge("Mixiuhca", "Velodromo");
  red.newEdge("Velodromo", "Ciudad Deportiva");
  red.newEdge("Ciudad Deportiva", "Puebla");
  red.newEdge("Puebla", "Pantitlan");
  // Linea A
  red.newEdge("Pantitlan", "Agricola Oriental");
  red.newEdge("Agricola Oriental", "Canal de San Juan");
  red.newEdge("Canal de San Juan", "Tepalcates");
  red.newEdge("Tepalcates", "Guelatao");
  red.newEdge("Guelatao", "Penion Viejo");
  red.newEdge("Penion Viejo", "Acatitla");
  red.newEdge("Acatitla", "Santa Marta");
  red.newEdge("Santa Marta", "Los Reyes");
  red.newEdge("Los Reyes", "La Paz");
  // Linea B
  red.newEdge("Buenavista", "Guerrero");
  red.newEdge("Guerrero", "Garibaldi");
  red.newEdge("Garibaldi", "Lagunilla");
  red.newEdge("Lagunilla", "Tepito");
  red.newEdge("Tepito", "Morelos");
  red.newEdge("Morelos", "San Lazaro");
  red.newEdge("San Lazaro", "Flores Magon");
  red.newEdge("Flores Magon", "Romero Rubio");
  red.newEdge("Romero Rubio", "Oceania");
  red.newEdge("Oceania", "Deportivo Oceania");
  red.newEdge("Deportivo Oceania", "Bosque de Aragon");
  red.newEdge("Bosque de Aragon", "Villa de Aragon");
  red.newEdge("Villa de Aragon", "Nezahualcoyotl");
  red.newEdge("Nezahualcoyotl", "Impulsora");
  red.newEdge("Impulsora", "Rio de los Remedios");
  red.newEdge("Rio de los Remedios", "Muzquiz");
  red.newEdge("Muzquiz", "Ecatepec");
  red.newEdge("Ecatepec", "Olimpica");
  red.newEdge("Olimpica", "Plaza Aragon");
  red.newEdge("Plaza Aragon", "Ciudad Azteca");
  // LINEA 12
  red.newEdge("Tlahuac", "Tlaltenco");
  red.newEdge("Tlaltenco", "Zapotitlan");
  red.newEdge("Zapotitlan", "Nopalera");
  red.newEdge("Nopalera", "Olivos");
  red.newEdge("Olivos", "Tezonco");
  red.newEdge("Tezonco", "Periferico Oriente");
  red.newEdge("Periferico Oriente", "Calle 11");
  red.newEdge("Calle 11", "Lomas Estrella");
  red.newEdge("Lomas Estrella", "San Andres Tomatlan");
  red.newEdge("Lomas Estrella", "Culhuacan");
  red.newEdge("Culhuacan", "Atlalilco");
  red.newEdge("Atlalilco", "Mexicaltzingo");
  red.newEdge("Mexicaltzingo", "Ermita");
  red.newEdge("Ermita", "Eje Central");
  red.newEdge("Eje Central", "Parque de los Venados");
  red.newEdge("Parque de los Venados", "Zapata");
  red.newEdge("Zapata", "Hospital 20 de noviembre");
  red.newEdge("Hospital 20 de noviembre", "Insurgentes Sur");
  red.newEdge("Insurgentes Sur", "Mixcoac");
  
  return red;
}