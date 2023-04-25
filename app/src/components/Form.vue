<template>
    <FormKitSchema :schema="schema" :data="data" />
</template>
  
<script setup lang="ts">
import { ref } from "vue"
import { FormKitSchema } from '@formkit/vue'

type Schema = InstanceType<typeof FormKitSchema>["$props"]["schema"];
type Data = { formValue: Record<string, any>, handleSubmit: (target: any) => Promise<void> };

const schema = ref<Schema>([])

const data = ref<Data>({
    formValue: {},

    handleSubmit: async (target) => {
        await fetch("/config/set", {
            method: "POST",
            credentials: "include",
            headers: {
                "Content-Type": "application/json",
            },
            body: JSON.stringify(target)
        }).then(() => {
            alert("Configuration done!")
        })
    }
})

/**
 * Extracts values having key 'name' from a nested object
 */
function getNames(obj: any) {
    let names: string[] = [];
    for (let key in obj) {
        if (typeof obj[key] === "object") {
            names = names.concat(getNames(obj[key]));
        } else if (key === "name") {
            names.push(obj[key]);
        }
    }
    return names;
}

try {
    await fetch("/schema.json", {
        method: "GET",
        headers: {
            "Accept": "application/json",
        },
    }).then(async (res) => {
        const content = await res.json()
        Object.assign(schema.value, content)
    })

    const names = getNames(schema.value)

    names.forEach(name => data.value.formValue[name] = "")

    await fetch("/config/get", {
        method: "POST",
        credentials: "include",
        headers: {
            "Accept": "application/json",
            "Content-Type": "application/json",
        },
        body: JSON.stringify(data.value.formValue)
    }).then(async (res) => {
        const content = await res.json()
        Object.assign(data.value.formValue, content)
    })
} catch (error) {
    alert(error)
}
</script>