package com.satragno.ejerciciosgrafos;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class Main {
    public static void main(String[] args) {
        File archivo = new File("princesa.in");
        try (FileReader reader = new FileReader(archivo);
             BufferedReader bReader = new BufferedReader(reader)) {
            String linea[] = bReader.readLine().split(" ");
            int claros = Integer.parseInt(linea[0]);
            
            linea = bReader.readLine().split(" ");
            int posicionPrincesa = Integer.parseInt(linea[0]);
            int posicionPrincipe = Integer.parseInt(linea[1]);
            
            linea = bReader.readLine().split(" ");
            List<Integer> posicionDragones = new ArrayList<Integer>();
            if (!(linea.length == 1 && linea[0].isEmpty())) {
                for (String posicion : linea)
                    posicionDragones.add(Integer.parseInt(posicion));
            }
                
            List<LineaNodo> lineas = new ArrayList<LineaNodo>();
            String lineaNodo;
            while ((lineaNodo = bReader.readLine()) != null) {
                linea = lineaNodo.split(" ");
                lineas.add(new LineaNodo(Integer.parseInt(linea[0]) - 1,
                                         Integer.parseInt(linea[1]) - 1,
                                         Integer.parseInt(linea[2])));
            }
            
            Grafo grafo = new Grafo(lineas, claros);
            
            Integer[] largoCaminos = grafo.dijkstra(posicionPrincesa - 1);
            
            String respuesta = "ERROR DE PROGRAMACIÓN";
            boolean interceptado = false;
            Integer largoPrincipe = largoCaminos[posicionPrincipe - 1]; 
            if (largoPrincipe == null) {
                respuesta = "NO HAY CAMINO";
            } else {
                for (int posicionDragon : posicionDragones) {
                    if (largoCaminos[posicionDragon - 1] != null &&
                        largoCaminos[posicionDragon - 1] <= largoPrincipe) {
                        respuesta = "INTERCEPTADO";
                        interceptado = true;
                        break;
                    }
                }
                if (!interceptado) {
                    respuesta = "";
                    List<Integer> camino = grafo.getCamino(posicionPrincipe - 1); 
                    for (int j = 0; j < camino.size() - 1; j++)
                        respuesta += (camino.get(j) + 1) + " ";
                    respuesta += camino.get(camino.size() - 1) + 1;
                }
            }
            
            File archivoSalida = new File("./princesa.out");
            try (FileWriter writer = new FileWriter(archivoSalida)) {
                writer.write(respuesta);
            }
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
    }
}
