import "./styles/input.css";

interface Props {
    id: string;
    selected: boolean;
    placeholder: string;
    defaultValue: string;
    onChange: (element: any) => void;
    setSelected: (selected: boolean) => void;
};

const Input = (props: Props) => {
    const {
        id,
        selected,
        placeholder,
        defaultValue,
        onChange,
        setSelected
    } = props;
    
    const onSelect = () => setTimeout(() => setSelected(!selected), 100);

    return (
        <input
            className="fields"
            type="text"
            name={id}
            id={id}
            value={defaultValue}
            placeholder={selected ? "" : placeholder}
            onFocus={onSelect}
            onBlur={onSelect}
            onChange={onChange}
        />
    );
};

export default Input;