class Ll_Node<T> {
    /**
     * Linkedlist Node Implementation
     * data field stores the value to be stored
     * next field points to the next node in the linkedlist
     * prev field points to the previous node in the linkedlist
     */
    data: T;
    next: Ll_Node<T> | null;
    prev: Ll_Node<T> | null;

    constructor( data: T, next: Ll_Node<T> | null = null, prev: Ll_Node<T> | null = null ){
        this.next = next;
        this.prev = prev;
        this.data = data;
    }
}

class Linkedlist<T> {
    /**
     * Linkedlist implementation
     * head field points to the beginning of the linkedlist
     * tail field points to the end of the linkedlist
    */
    head: Ll_Node<T> | null;
    tail: Ll_Node<T> | null;
    size: number;

    constructor( head: Ll_Node<T> | null = null, tail: Ll_Node<T> | null = null ){
        this.head = head;
        this.tail = tail;
        this.size = 0;
    }

    // creates and returns a linkedlist object
    ll_create(): Linkedlist<T> {
        return new Linkedlist();
    }

    // adds a node to the front of the list, storing the given data in the node
    ll_push(data: T) {
        let node = new Ll_Node(data);

        if( this.head != null ) {
            this.head.prev = node;
            node.next = this.head;
        } else {
            this.tail = node;
        }

        this.head = node;
        this.size += 1;
    }

    // removes the node at the front of the list and returns the associated data.
    ll_pop(): T | null {
        let node = this.head
        if( node === null ) return null;

        this.head = node.next;
        this.size -= 1;
        if( this.head === null ){
            this.tail = null;
        } else {
            this.head.prev = null;
        }

        return node.data;
    }

    // adds a node to the end of the list, storing the given data in the node.
    ll_append( data: T ) {
        let node = new Ll_Node(data);

        if( this.tail != null ){
            node.prev = this.tail;
            this.tail.next = node;
        } else {
            this.head = node;
        }
        
        this.tail = node;
        this.size += 1;
    }

    // removes the first node in the list whose data matches target given the comparison function.
    // The function returns the pointer to the data in the removed node.
    ll_remove( target: T, compfunc: (a: T, b: T) => number ): T | null {
        if( !this.head || target === null || !compfunc ) return null;

        let node: Ll_Node<T> | null = this.head;

        while( node !== null ) {
            if( compfunc( node.data, target ) === 0 ){
                const data = node.data;

                // fix prev link
                if (node.prev !== null) {
                    node.prev.next = node.next;
                } else {
                    this.head = node.next; // removing head
                }

                // fix next link
                if (node.next !== null) {
                    node.next.prev = node.prev;
                } else {
                    this.tail = node.prev; // removing tail
                }

                this.size -= 1;
                return data;
            }

            node = node.next;
        }

        return null;
    }

    // finds the first node in the list whose data matches target given the comparison function. The function 
    // returns the pointer to the data in the node. If the target is not in the list, then the function returns NULL.
    ll_find( target: T, compfunc: (a: T, b: T) => number ): T | null {
        if( !this.head || target === null || !compfunc ) return null;

        let node: Ll_Node<T> | null = this.head;

        while( node !== null ) {
            if( compfunc( node.data, target ) === 0 ){
                return node.data;
            }

            node = node.next;
        }

        return null;
    }

    // returns the size of the list.
    ll_size(): number {
        return this.size
    }

    // removes all of the nodes from the list, freeing the associated data using the given function.
    ll_clear() {
        let node: Ll_Node<T> | null = this.head;

        while (node !== null) {
            const next = node.next;

            node.next = null;
            node.prev = null;

            node = next;
        }

        this.head = null;
        this.tail = null;
        this.size = 0;
    }

    // traverses the list and applies the given function to the data at each node.
    ll_map( mapfunc: (data: T) => void ) {
        if (!this.head || !mapfunc) return;

        let node: Ll_Node<T> | null = this.head;

        while (node !== null) {
            mapfunc(node.data);
            node = node.next;
        }
    }

}