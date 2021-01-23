#pragma once
using namespace System;
namespace BodegaGrid {
	public ref class Inventario {
	private:
		//costo inventario
		double costo_total;
		//tipo de item
		int tipo;
		//tipo de unidades
		int unidades;
	public:
		//constructor
		Inventario() {
			costo_total = 0;
			tipo = 0;
			unidades = 0;
		}
		//getters
		property int Type {
			int get() {
				return tipo;
			}
		}
		property int Units {
			int get() {
				return unidades; // ver que pedo con esto 
			}
		}
		property double Price {
			double get() {
				return costo_total;
			}
		}
		//setters
		void SetFinalCost(double cost) {
			costo_total += cost;
		}
		void SetType(int tipo) {
			this->tipo = tipo;
		}
		void SetUnits(int cant) {
			unidades += cant;
		}
	};
	public ref class Kardex {
	private:
		//tipo de movimiento
		String^ movimiento;
		//codigo 
		String^ code;
		//responsable
		String^ responsable;
		//bahias entrada y salida
		String^ entrada;
		String^ salida;
		//fecha
		String^ fecha;
		//unidades
		int cant;
		//precios
		double precio_u;
		double precio_tI;
	public:
		//constructores
		Kardex() {
			movimiento = "";
			code = "";
			responsable = "";
			cant = 0;
			precio_u = 0;
			precio_tI = 0;
		}
		//getters
		property String^ Movement {
			String^ get() {
				return movimiento;
			}
		}
		property String^ Code {
			String^ get() {
				return code;
			}
		}
		property String^ Responsible {
			String^ get() {
				return responsable;
			}
		}
		property String^ Entrance {
			String^ get() {
				return entrada;
			}
		}
		property String^ Exit {
			String^ get() {
				return salida;
			}
		}
		property String^ Date {
			String^ get() {
				return fecha;
			}
		}
		property int Size {
			int get() {
				return cant;
			}
		}
		property double Price_Unit {
			double get() {
				return precio_u;
			}
		}
		property int Total {
			int get() {
				return precio_tI;
			}
		}
		//setters
		void SetMovement(String^ move) {
			movimiento = move;
		}
		void SetCode(String^ code) {
			this->code = code;
		}
		void SetResponsible(String^ name) {
			responsable = name;
		}
		void SetQuantity(int cant) {
			this->cant = cant;
		}
		void SetPrice(double price) {
			precio_u = price;
		}
		void SetTotal(double total) {
			precio_tI = total;
		}
		void SetSalidaEntrada(String^ ID_Salida, String^ ID_Entrada) {
			entrada = ID_Entrada;
			salida = ID_Salida;
		}
		void SetDate(String^ date) {
			fecha = date;
		}
	};
}