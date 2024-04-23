import React, { useContext } from 'react';
import { Link } from 'react-router-dom';
import { CartContext } from '../store/Cart/context';
import { FavoritesContext } from '../store/Favorites/context';

export function Header() {
  const { state } = useContext(CartContext);
  const { state: favoritesState } = useContext(FavoritesContext);

  const favoritesCount = favoritesState ? favoritesState.products.length : 0;

  return (
    <header>
      <div className="d-flex justify-content-between mx-4">
        <Link to="/">Home</Link>
        <div>
          <Link to="/products" className="p-3">
            Products
          </Link>
          <Link to="/cart">Cart ({state.products.length})</Link>
          <Link to="/favorites" className="p-3">
            🤍 ({favoritesCount})
          </Link>
        </div>
      </div>
    </header>
  );
}
