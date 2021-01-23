#pragma once
using namespace System;

namespace BodegaGrid {
	public ref class Item {
	private:
		//tipo de item entrante
		int type;
		//precio por unidad
		double precio_u;
		//peso por unidad
		double peso_u;
		//unidades
		int unidades;
	public:
		//constructor
		Item() {
			type = 0;
			unidades = 0;
			precio_u = 0;
			peso_u = 0;
		}
		//getters
		property int Type {
			int get() {
				return type;
			}
		}
		property double Price_u {
			double get() {
				return precio_u;
			}
		}
		property int Unidades {
			int get() {
				return unidades;
			}
		}
		property double PesoU {
			double get() {
				return peso_u;
			}
		}
		//setters
		void SetType(int tipo) {
			type = tipo;
		}
		void SetPrice(double precio) {
			precio_u = precio;
		}
		void SetUnits(int unidad) {
			unidades = unidad;
		}
		void SetWeight(double weight) {
			peso_u = weight;
		}
	};	
}

	