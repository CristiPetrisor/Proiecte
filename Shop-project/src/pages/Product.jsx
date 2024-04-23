import React, { useEffect, useState, useContext } from 'react';
import Button from 'react-bootstrap/Button';
import { useParams } from 'react-router-dom';
// Importam ce avem nevoie.
import { CartContext } from '../store/Cart/context';
import { addToCart } from '../store/Cart/actions';
import { addToFavorites } from '../store/Favorites/actions';

export function Product() {
  // Vom modifica state-ul cart-ului, deci avem nevoie de dispatch.
  const { dispatch } = useContext(CartContext);
  let { id } = useParams();
  id = decodeURI(id);
  const [product, setProduct] = useState({});
  useEffect(() => {
    fetch(`https://www.cheapshark.com/api/1.0/deals?id=${id}`)
      .then((response) => response.json())
      .then((product) => {
        setProduct(product);
      });
  }, [id]);

  function handleAddToCart(product) {
    // Apelam actiunea, cu payload-ul aferent.
    const actionResult = addToCart(product);
    // Trimitem rezultatul actiunii catre reducer.
    dispatch(actionResult);
  }

  function handleAddToFavorites(product) {
    const actionResult = addToFavorites(product);
    favoritesDispatch(actionResult);
  }

  const productInfo = product.gameInfo || {};
  const { thumb, name, salePrice, retailPrice } = productInfo;

  return (
    <div className="d-flex my-3 px-2">
      <div className="w-50">
        <div>
          <img src={thumb} alt="" />
        </div>
        <h1>{name}</h1>
      </div>
      <div className="w-50">
        <p>Preț întreg: {retailPrice}$</p>
        <p>
          Preț redus: <span className="text-danger">{salePrice}$</span>
        </p>
        <Button
          variant="success"
          onClick={() => {
            // Construim payload-ul si il pasam ca argument functiei care va apela actiunea addToCart.
            handleAddToCart({
              id,
              image: thumb,
              name: name,
              price: retailPrice,
            });
          }}
        >
          Adaugă în coș
        </Button>
        <Button
          variant="primary"
          onClick={() => {
            handleAddToFavorites({
              id,
              image: thumb,
              name: name,
              price: retailPrice,
            });
          }}
        >
          Adaugă la favorite
        </Button>
      </div>
    </div>
  );
}
