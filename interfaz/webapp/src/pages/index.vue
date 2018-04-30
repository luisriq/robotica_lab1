<template>
  <q-page>
  	<q-list class="">
	  <q-item class="row">
	    <q-item-side icon="brightness_medium" />
	    <q-item-main label="Giro">
	      <q-slider @input="val => { angulo(val, 0) }" :value="giro" :min="0" :max="180" label />
	    </q-item-main>
	  </q-item>
	  <q-item>
	    <q-item-side icon="brightness_medium" />
	    <q-item-main label="Altura">
	      <q-slider @input="val => { angulo(val, 1) }" :value="altura" :min="10" :max="125" label />
	    </q-item-main>
	  </q-item>
	  <q-item>
	    <q-item-side icon="brightness_medium" />
	    <q-item-main label = "Horizontal">
	      <q-slider @input="val => { angulo(val, 2) }" :value="adelante" :min="65" :max="150" label />
	    </q-item-main>
	  </q-item>
	  <q-item>
	    <q-item-side icon="brightness_medium" />
	    <q-item-main  label = "Pinzas">
	      <q-slider @input="val => { angulo(val, 3) }" :value="pinzas" :min="1" :max="180" label />
	    </q-item-main>
	  </q-item>
	</q-list>

  </q-page>
</template>

<style>
</style>

<script>
export default {
  name: 'PageIndex',
  methods: {
  	angulo: function (value, servo) {
  		console.log(value)
  		console.log(servo)
  		var nuevoTiempo = new Date()
  		console.log(nuevoTiempo - this.tiempo)
  		if ((nuevoTiempo - this.tiempo) > 300) {
  			this.tiempo = new Date()
  			this.$axios.post('/api/mover/',{servo:servo, grados:value})
  		}
  		
  		
  	}
  },
  data : function (){
  	return {
  		tiempo: new Date(),
  		giro : 90,
  		altura : 80,
  		adelante : 65,
  		pinzas : 5
  	}
  } 
}
</script>
