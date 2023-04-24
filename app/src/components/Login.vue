<template>
    <FormKitSchema :schema="schema" />
</template>

<script setup lang="ts">
import { FormKitSchema } from '@formkit/vue'

type Schema = InstanceType<typeof FormKitSchema>["$props"]["schema"];

const schema: Schema = [
    {
        $formkit: "form",
        submitLabel: "Login",
        action: "http://localhost:3000",
        method: "post",
        // submitAttrs: {
        //     style: { width: '100%', 'text-align': 'center' }
        // },
        children: [ 
            {
                $formkit: 'text',
                name: 'email',
                label: 'Email',
                help: 'This will be used for your account.',
                validation: 'required|email',
            },
            {
                $formkit: 'password',
                name: 'password',
                label: 'Password',
                help: 'Enter your new password.',
                validation: 'required|length:5,16',
            },
        ]
    },
]
</script>