export class RequestBodyEmail {
    constructor(
        public name: string,
        public validator: string,
        public email: string
    ) {

    }
}

export class RequestBodyName {
    constructor(
        public name: string,
        public validator: string
    ) {

    }
}
