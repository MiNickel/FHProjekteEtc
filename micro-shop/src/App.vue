<template>
  <v-app>
    <v-app-bar app color="primary" dark>
      <div class="d-flex align-center">
        <v-img
          alt="Vuetify Logo"
          class="shrink mr-2"
          contain
          src="https://cdn.vuetifyjs.com/images/logos/vuetify-logo-dark.png"
          transition="scale-transition"
          width="40"
        />

        <v-img
          alt="Vuetify Name"
          class="shrink mt-1 hidden-sm-and-down"
          contain
          min-width="100"
          src="https://cdn.vuetifyjs.com/images/logos/vuetify-name-dark.png"
          width="100"
        />
      </div>

      <v-spacer></v-spacer>

      <v-btn
        href="https://github.com/vuetifyjs/vuetify/releases/latest"
        target="_blank"
        text
      >
        <span class="mr-2">Latest Release</span>
        <v-icon>mdi-open-in-new</v-icon>
      </v-btn>
    </v-app-bar>

    <v-main>
      <div id="paypal"></div>
      <router-view />
    </v-main>
  </v-app>
</template>

<script>
import { loadScript } from '@paypal/paypal-js';
export default {
  name: "App",

  data: () => ({
    //
  }),
  async mounted() {
      const paypalSdk = await loadScript({
        "client-id": "ASchRjlk4vOH0uRd5BwQ3Lt408sw_7wydEShg63KSyxkA5tVrIWRyJhSWZc8Ig8TFXRVRVEan3d6Ufe4",
        "currency": "EUR"
      });
      paypalSdk.Buttons().render("#paypal");
  }
    
  
};
</script>
