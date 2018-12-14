
void BlockTransposeInPlace( const Eigen::Index colBlock )
{
    const Eigen::Index nc = this->cols();
    const Eigen::Index nr = this->rows();

    eigen_assert( !( nc % colBlock ) && "The blocksize is not compatible with number of columns." );

    if ( nr == 1 || colBlock == 1 )
    {
        this->resize( colBlock, this->size() / colBlock );
    }
    else if ( nr == colBlock )
    {
        for ( index_t j = 0; j != nc; j += colBlock )
            this->middleCols( j, colBlock )
                .template triangularView<Eigen::StrictlyUpper>()
                .swap( this->middleCols( j, colBlock ).transpose() );
    }
    else
    {
        Eigen::Map<Matrix> m( this->data(), nr, nc );
        this->resize( colBlock, this->size() / colBlock );

        index_t i = 0;
        for ( index_t j = 0; j != nc; j += colBlock, i += nr )
            this->middleCols( i, nr ) = m.middleCols( j, colBlock ).transpose().eval();
    }
}
