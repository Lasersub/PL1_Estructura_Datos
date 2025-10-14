#ifndef PEDIDO_H
#define PEDIDO_H


class Pedido
{
    public:
        /** Default constructor */
        Pedido();
        /** Default destructor */
        virtual ~Pedido();

        /** Access m_id_editorial
         * \return The current value of m_id_editorial
         */
        unsigned int Getid_editorial() { return m_id_editorial; }
        /** Set m_id_editorial
         * \param val New value to set
         */
        void Setid_editorial(unsigned int val) { m_id_editorial = val; }

    protected:

    private:
        unsigned int m_id_editorial; //!< Member variable "m_id_editorial"
};

#endif // PEDIDO_H
