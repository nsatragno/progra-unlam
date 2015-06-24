package com.satragno.ejerciciosgrafos;

public class LineaNodo {
    private int desde;
    private int hasta;
    private int peso;
    
    public LineaNodo(int desde, int hasta, int peso) {
        this.desde = desde;
        this.hasta = hasta;
        this.peso = peso;
    }

    /**
     * @return the desde
     */
    public int getDesde() {
        return desde;
    }

    /**
     * @return the hasta
     */
    public int getHasta() {
        return hasta;
    }

    /**
     * @return the peso
     */
    public int getPeso() {
        return peso;
    }
    
}
