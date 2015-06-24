package com.satragno.ejerciciosgrafos;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

public class Grafo {
    private Integer[][] matriz;
    private Integer[] predecesores;
    private int nodoInicial;
    
    public Grafo(List<LineaNodo> pares, int cantidadNodos) {
        matriz = new Integer[cantidadNodos][cantidadNodos];
        for (LineaNodo linea : pares) {
            matriz[linea.getDesde()][linea.getHasta()] = linea.getPeso();
            matriz[linea.getHasta()][linea.getDesde()] = linea.getPeso();
        }
    }

    public Integer[] dijkstra(int nodoInicial) {
        Integer[] distancias = new Integer[matriz.length];
        this.nodoInicial = nodoInicial;
        predecesores = new Integer[matriz.length];
        distancias[nodoInicial] = 0;
        
        Set<Integer> nodosNoVisitados = new HashSet<Integer>();
        for (int i = 0; i < matriz.length; i++) {
            if (i != nodoInicial)
                nodosNoVisitados.add(i);
        }
        
        int nodoActual = nodoInicial;
        while (!nodosNoVisitados.isEmpty()) {
            for (Integer vecino : getVecinos(nodoActual)) {
                if (nodosNoVisitados.contains(vecino)) {
                    int distanciaTentativa = matriz[nodoActual][vecino] + distancias[nodoActual];
                    if (distancias[vecino] == null || distanciaTentativa < distancias[vecino]) {
                        distancias[vecino] = distanciaTentativa;
                        predecesores[vecino] = nodoActual;
                    }
                }
            }
            nodosNoVisitados.remove(nodoActual);
            Integer proximoNodo = null;
            for (int nodoNoVisitado : nodosNoVisitados) {
                if (proximoNodo == null || distancias[proximoNodo] == null || 
                    distancias[nodoNoVisitado] != null && distancias[proximoNodo] > distancias[nodoNoVisitado])
                    proximoNodo = nodoNoVisitado;
            }
            if (proximoNodo == null)
                return distancias;
            nodoActual = proximoNodo;
        }
        
        return distancias;
    }

    private List<Integer> getVecinos(int nodoActual) {
        List<Integer> vecinos = new ArrayList<Integer>();
        for (int i = 0; i < matriz.length; i++) {
            if (matriz[nodoActual][i] != null)
                vecinos.add(i);
        }
        return vecinos;
    }

    public List<Integer> getCamino(int nodoHasta) {
        int i = nodoHasta;
        List<Integer> camino = new ArrayList<Integer>();
        camino.add(i);
        while (i != nodoInicial) {
            i = predecesores[i];
            camino.add(i);
        }
        List<Integer> caminoRevertido = new ArrayList<Integer>(camino.size());
        for (int j = camino.size() - 1; j >= 0; j--) {
            caminoRevertido.add(camino.get(j));
        }
        return caminoRevertido;
    }
}
