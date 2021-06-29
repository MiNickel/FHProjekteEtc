<template>
  <v-form v-model="valid">
    <v-container>
      <v-row>
        <v-col
          cols="12"
          md="4"
        >
          <v-text-field
            v-model="firstname"
            :rules="nameRules"
            :counter="10"
            label="First name"
            required
          ></v-text-field>
        </v-col>

        <v-col
          cols="12"
          md="4"
        >
          <v-text-field
            v-model="lastname"
            :rules="nameRules"
            :counter="10"
            label="Last name"
            required
          ></v-text-field>
        </v-col>

        <v-col
          cols="12"
          md="4"
        >
          <v-text-field
            v-model="email"
            :rules="emailRules"
            label="E-mail"
            required
          ></v-text-field>
        </v-col>
      </v-row>
    </v-container>
  </v-form>
</template>

<script lang="js">
import PaymentService from "@/payment/services/payment.service.js"
export default {
  name: "Payment",
  data() {
    return {
        test: {},
    }
  },
  async created() {
    try {
      const response = await PaymentService.test();
      console.log(response);
      this.test = response.data[0];
    } catch(e) {
      console.log(e);
    }
  }
};
</script>

<style>
h3 {
  color: #000;
}
</style>
